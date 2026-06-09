/*
 * File: ShootSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "MainHSM.h"
#include "ShootSubHSM.h"
#include "peashooter.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ISZState,
    ShootState,
} ShootSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "ISZState",
    "ShootState",
};




        /*******************************************************************************
         * PRIVATE FUNCTION PROTOTYPES                                                 *
         ******************************************************************************/
        /* Prototypes for private functions for this machine. They should be functions
           relevant to the behavior of this state machine */
        static void StartShootTurnStep(void);
        static void StartShootTurnPause(void);

        /*******************************************************************************
         * PRIVATE MODULE VARIABLES                                                            *
         ******************************************************************************/
        /* You will need MyPriority and the state variable; you may need others as well.
         * The type of state variable should match that of enum in header file. */

        static ShootSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;

/* ShootState stall-recovery phase: FALSE = indexer driving, TRUE = power cut
 * for the brief unstick window before the next breakaway kick. */
static uint8_t IndexerUnsticking = FALSE;

/* ShootState sweep phase: TRUE = drive motors tank-turning (one step),
 * FALSE = holding at the current angle so balls fire before the next step. */
static uint8_t ShootTurnStepping = FALSE;

/* Bounded-sweep tracking: the base ping-pongs over a 90 deg arc from its
 * post-180 start. ShootSweepGoingRight is the current turn direction;
 * ShootSweepElapsed accumulates active-turn ms in that direction and triggers a
 * reversal once it reaches SHOOT_SWEEP_TURN_TIME (one 90 deg edge). */
static uint8_t ShootSweepGoingRight = TRUE;
static uint16_t ShootSweepElapsed = 0;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitShootSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitShootSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunShootSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunShootSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */

/* ISZ: 180-degree tank turn before the shoot sweep. Turn time is derived
 * from the MainHSM.c calibration note (~1400 ms per 90 deg tank turn @ 700);
 * tune ISZ_TURN_TIME if the base over/under-rotates. */
#define ISZ_TURN_POWER 700
#define ISZ_TURN_TIME 1800

/* ShootState PWM duties, mirroring HSM.X HSMService.c ShootState. The indexer
 * runs at full duty for INDEXER_FULL_TIME to seat the first ball, then drops to
 * the steady run duty. PS_Set* take 0..PEASHOOTER_MAX_SPEED (1000), so
 * INDEXER_FULL_DUTY 1000 maps to MAX_PWM (HSM_INDEXER_FULL_DUTY). */
#define TOP_SHOOTER_DUTY 850      /* HSM_UPPER_SHOOTER_DUTY */
#define BOT_SHOOTER_DUTY 350      /* HSM_LOWER_SHOOTER_DUTY */
#define INDEXER_FULL_DUTY 1000    /* HSM_INDEXER_FULL_DUTY (MAX_PWM) */
#define INDEXER_RUN_DUTY 1000      /* HSM_INDEXER_RUN_DUTY */
#define INDEXER_FULL_TIME 1000    /* HSM_INDEXER_FULL_TIME_MS */

/* Open-loop stall recovery. The indexer has no encoder or current sense and
 * runs on a single-direction PWM pin, so once it stalls on a ball or a cogging
 * dead-spot at a fixed duty it cannot supply its own breakaway torque to
 * restart -- you have to nudge it by hand. To do that automatically we cycle
 * the drive: run normally for INDEXER_KICK_PERIOD, then cut power for
 * INDEXER_UNSTICK_TIME so a stalled rotor relaxes, then slam full duty to get a
 * fresh breakaway kick. Tune the two periods to taste (longer kick period =
 * less stutter when healthy, shorter = faster stall recovery). */
#define INDEXER_KICK_PERIOD 350   /* ms of normal drive between recovery pulses */
#define INDEXER_UNSTICK_TIME 45   /* ms of power-off to let a stalled rotor relax */

/* Shoot sweep: after the ISZ 180 the base ping-pongs over a bounded 90 deg arc
 * while the shooters and indexer run, spraying balls across the region. From the
 * post-180 start it step-turns right until it has covered SHOOT_SWEEP_TURN_TIME
 * (one 90 deg edge), then step-turns left back to the start, and repeats. Each
 * step drives the base briefly (SHOOT_STEP_DRIVE_TIME) then holds
 * (SHOOT_STEP_PAUSE_TIME) so shots land at the current angle. This runs on
 * SWEEP_TIMER, independent of the REV_TIMER indexer cycling -- PS_Stop() only
 * zeroes the drive motors, so the shooters/indexer keep running across a step.
 * Tune power for step torque, the two times for step size and dwell. */
#define SHOOT_TURN_POWER 500      /* same magnitude/direction as ISZ_TURN_POWER */
#define SHOOT_STEP_DRIVE_TIME 150 /* ms of turning per increment (step size) --
                                   * must exceed the base's spin-up time (~50-150ms)
                                   * or each step is a twitch that looks stationary */
#define SHOOT_STEP_PAUSE_TIME 300 /* ms held at each angle to let balls fire */

/* Total active-turn time for one 90 deg sweep edge. The ISZ turn is a known 180
 * at the same power, so half its time is 90 deg and tracks the same turn
 * calibration automatically -- retune by adjusting ISZ_TURN_TIME. */
#define SHOOT_SWEEP_TURN_TIME (1400 / 2)

ES_Event RunShootSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    ShootSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // now put the machine into the actual initial state
                nextState = ISZState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ISZState: // 180-degree tank turn, then go straight to the shoot sweep
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    printf("SHOOT: ISZ 180 tank turn\n");
                    PS_Stop();
                    PS_TankTurnRightContinuous(ISZ_TURN_POWER);
                    ES_Timer_InitTimer(REV_TIMER, ISZ_TURN_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == REV_TIMER) {
                        printf("SHOOT: ISZ turn complete -> SHOOT (no beacon)\n");
                        PS_Stop();
                        nextState = ShootState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(REV_TIMER);
                    PS_Stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // pass unhandled events back up to the next level
                    break;
            }
            break;

        case ShootState: // spin shooters + indexer at the HSM.X PWM duties
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    printf("SHOOT: SHOOT top=%d bot=%d indexer full\n",
                            TOP_SHOOTER_DUTY, BOT_SHOOTER_DUTY);
                    PS_Stop();
                    PS_SetTopShooter(TOP_SHOOTER_DUTY);
                    PS_SetBotShooter(BOT_SHOOTER_DUTY);
                    PS_SetIndexer(INDEXER_FULL_DUTY);
                    IndexerUnsticking = FALSE; // start in the driving phase
                    ES_Timer_InitTimer(REV_TIMER, INDEXER_FULL_TIME);
                    ShootSweepGoingRight = TRUE; // sweep right to +90, back to start, repeat
                    ShootSweepElapsed = 0;
                    StartShootTurnStep(); // begin the bounded shoot sweep
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SWEEP_TIMER) {
                        // Shoot sweep step boundary: alternate a turn step with a
                        // hold so balls fire at each angle. Drive motors only; the
                        // shooters/indexer keep running.
                        if (ShootTurnStepping) {
                            // A turn step just finished: bank the angle covered and
                            // reverse direction once we reach the 90 deg edge (or
                            // come back to the start).
                            ShootSweepElapsed += SHOOT_STEP_DRIVE_TIME;
                            if (ShootSweepElapsed >= SHOOT_SWEEP_TURN_TIME) {
                                ShootSweepGoingRight = !ShootSweepGoingRight;
                                ShootSweepElapsed = 0;
                            }
                            StartShootTurnPause();
                        } else {
                            StartShootTurnStep();
                        }
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam == REV_TIMER) {
                        // Shooters were commanded on entry; only the indexer is
                        // cycled here for stall recovery.
                        if (!IndexerUnsticking) {
                            // Drive window elapsed: cut power briefly so a
                            // stalled rotor can relax before the next kick.
                            PS_SetIndexer(0);
                            IndexerUnsticking = TRUE;
                            ES_Timer_InitTimer(REV_TIMER, INDEXER_UNSTICK_TIME);
                        } else {
                            // Re-apply full duty for maximum breakaway torque,
                            // then resume the drive window.
                            PS_SetIndexer(INDEXER_RUN_DUTY);
                            IndexerUnsticking = FALSE;
                            ES_Timer_InitTimer(REV_TIMER, INDEXER_KICK_PERIOD);
                        }
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_EXIT:
                    // Stop both timers, the drive base, and all shoot outputs so
                    // nothing keeps running (or fires stray timeouts) after Shoot.
                    ES_Timer_StopTimer(REV_TIMER);
                    ES_Timer_StopTimer(SWEEP_TIMER);
                    PS_Stop();
                    PS_SetIndexer(0);
                    PS_SetTopShooter(0);
                    PS_SetBotShooter(0);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // pass unhandled events back up to the next level
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) {
    RunShootSubHSM(EXIT_EVENT);
    CurrentState = nextState;
    ThisEvent = RunShootSubHSM(ENTRY_EVENT);
}

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/* One increment of the shoot sweep: tank-turn in the current sweep direction for
 * SHOOT_STEP_DRIVE_TIME. Touches the drive motors only -- the shooters and
 * indexer set on ShootState entry keep running. */
static void StartShootTurnStep(void)
{
    ShootTurnStepping = TRUE;
    if (ShootSweepGoingRight) {
        PS_TankTurnRightContinuous(SHOOT_TURN_POWER);
    } else {
        PS_TankTurnLeftContinuous(SHOOT_TURN_POWER);
    }
    ES_Timer_InitTimer(SWEEP_TIMER, SHOOT_STEP_DRIVE_TIME);
}

/* Hold between increments for SHOOT_STEP_PAUSE_TIME so balls fire at the current
 * angle before the next step. PS_Stop() zeroes only the drive motors, so the
 * shooters and indexer are unaffected. */
static void StartShootTurnPause(void)
{
    ShootTurnStepping = FALSE;
    PS_Stop();
    ES_Timer_InitTimer(SWEEP_TIMER, SHOOT_STEP_PAUSE_TIME);
}
