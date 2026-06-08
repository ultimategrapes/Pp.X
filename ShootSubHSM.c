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
#include "FindBeaconSubHSM.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ISZState,
    AimLockOnState,
    ShootState,
} ShootSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "ISZState",
    "AimLockOnState",
    "ShootState",
};




        /*******************************************************************************
         * PRIVATE FUNCTION PROTOTYPES                                                 *
         ******************************************************************************/
        /* Prototypes for private functions for this machine. They should be functions
           relevant to the behavior of this state machine */

        /*******************************************************************************
         * PRIVATE MODULE VARIABLES                                                            *
         ******************************************************************************/
        /* You will need MyPriority and the state variable; you may need others as well.
         * The type of state variable should match that of enum in header file. */

        static ShootSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


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

/* ISZ: 180-degree tank turn before the beacon search. Turn time is derived
 * from the MainHSM.c calibration note (~1400 ms per 90 deg tank turn @ 700);
 * tune ISZ_TURN_TIME if the base over/under-rotates. */
#define ISZ_TURN_POWER 700
#define ISZ_TURN_TIME 2800

/* ShootState PWM duties, mirroring HSM.X HSMService.c ShootState. The indexer
 * runs at full duty for INDEXER_FULL_TIME to seat the first ball, then drops to
 * the steady run duty. PS_Set* take 0..PEASHOOTER_MAX_SPEED (1000), so
 * INDEXER_FULL_DUTY 1000 maps to MAX_PWM (HSM_INDEXER_FULL_DUTY). */
#define TOP_SHOOTER_DUTY 850      /* HSM_UPPER_SHOOTER_DUTY */
#define BOT_SHOOTER_DUTY 350      /* HSM_LOWER_SHOOTER_DUTY */
#define INDEXER_FULL_DUTY 1000    /* HSM_INDEXER_FULL_DUTY (MAX_PWM) */
#define INDEXER_RUN_DUTY 400      /* HSM_INDEXER_RUN_DUTY */
#define INDEXER_FULL_TIME 1000    /* HSM_INDEXER_FULL_TIME_MS */

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

        case ISZState: // 180-degree tank turn, then hand off to the beacon search
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
                        printf("SHOOT: ISZ turn complete -> AIM_LOCK_ON\n");
                        PS_Stop();
                        nextState = AimLockOnState;
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

        case AimLockOnState: // beacon detection via the stepped tank-turn search
            if (ThisEvent.EventType == ES_ENTRY) {
                InitFindBeaconSubHSM();
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == ES_EXIT) {
                RunFindBeaconSubHSM(EXIT_EVENT);
                ThisEvent.EventType = ES_NO_EVENT;
            } else {
                ThisEvent = RunFindBeaconSubHSM(ThisEvent);
            }

            switch (ThisEvent.EventType) {
                case BEACON_DETECTED:
                    printf("SHOOT: BEACON_DETECTED -> SHOOT\n");
                    PS_Stop();
                    nextState = ShootState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
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
                    ES_Timer_InitTimer(REV_TIMER, INDEXER_FULL_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == REV_TIMER) {
                        printf("SHOOT: indexer drop to run duty\n");
                        PS_SetTopShooter(TOP_SHOOTER_DUTY);
                        PS_SetBotShooter(BOT_SHOOTER_DUTY);
                        PS_SetIndexer(INDEXER_RUN_DUTY);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
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
