/*
 * File: TraverseFieldSubHSM.c
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
#include "TraverseFieldSubHSM.h"
#include "AlignTapeSubHSM.h"
#include "RideFrontSubHSM.h"
#include "RideLeftSubHSM.h"
#include "RideRightSubHSM.h"
#include "AvoidSubHSM.h"
#include "peashooter.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    Init,
    AlignFront,
    AlignRight,
    AlignLeft,
    RideFront,
    RideLeft,
    RideRight,
    AvoidRight,
    AvoidLeft,
    Stop,
} TraverseFieldSubHSMState_t;

static const char *StateNames[] = {
    "Init",
    "AlignFront",
    "AlignRight",
    "AlignLeft",
    "RideFront",
    "RideLeft",
    "RideRight",
    "AvoidRight",
    "AvoidLeft",
    "Stop",
};

typedef enum {
    AvoidBackingUp,
    AvoidTurningAway,
    AvoidDrivingForward,
    AvoidAligningTape,
    AvoidTurningBack,
} AvoidPhase_t;

static AvoidPhase_t AvoidPhase = AvoidBackingUp;

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

static TraverseFieldSubHSMState_t CurrentState = Init; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTraverseFieldSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTraverseFieldSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = Init;
    returnEvent = RunTraverseFieldSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTraverseFieldSubHSM(ES_Event ThisEvent)
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

#define ALINGFRONT_BACKWARD_TIME 500
#define ALINGRIGHT_BACKWARD_TIME 400
#define ALINGLEFT_BACKWARD_TIME 400


#define FRONTTORIGHT_TURNRIGHT_TIMER 900
#define FRONTTORIGHT_TURNRIGHT_SPEED 700

#define LEFTTORIGHT_TURNRIGHT_TIMER 900
#define LEFTTORIGHT_TURNRIGHT_SPEED 700

#define RIGHTTOLEFT_TURNRIGHT_TIMER 900
#define RIGHTTOLEFT_TURNRIGHT_SPEED 700


#define RIGHTTOISZ_TURNRIGHT_TIMER 1100
#define RIGHTTOISZ_TURNRIGHT_SPEED 700

#define LEFTTOISZ_TURNRIGHT_TIMER 1100
#define LEFTTOISZ_TURNRIGHT_SPEED 700


#define AVOIDRIGHT_BACKWARD_SPEED 700
#define AVOIDRIGHT_BACKWARD_TIME  500
#define AVOIDRIGHT_TURNRIGHT_SPEED     700
#define AVOIDRIGHT_TURNRIGHT_TIME      900
#define AVOIDRIGHT_TURNLEFT_SPEED     700
#define AVOIDRIGHT_TURNLEFT_TIME      1000
#define AVOIDRIGHT_FORWARD_SPEED  700
#define AVOIDRIGHT_FORWARD_TIME   3000
#define AVOIDRIGHT_FINALTURN_SPEED 700
#define AVOIDRIGHT_FINALTURN_TIME  1200

#define AVOIDLEFT_BACKWARD_SPEED 700
#define AVOIDLEFT_BACKWARD_TIME  500
#define AVOIDLEFT_TURNRIGHT_SPEED     700
#define AVOIDLEFT_TURNRIGHT_TIME      900
#define AVOIDLEFT_TURNLEFT_SPEED     700
#define AVOIDLEFT_TURNLEFT_TIME      1000
#define AVOIDLEFT_FORWARD_SPEED  700
#define AVOIDLEFT_FORWARD_TIME   3200
#define AVOIDLEFT_FINALTURN_SPEED 700
#define AVOIDLEFT_FINALTURN_TIME  1200

ES_Event RunTraverseFieldSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TraverseFieldSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case Init: // State: initialize TraverseField and enter first tape alignment.
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                InitAlignTapeSubHSM();
                InitRideFrontSubHSM();
                InitRideRightSubHSM();
                InitRideLeftSubHSM();
                InitAvoidSubHSM();
                // now put the machine into the actual initial state
                //                                nextState = RideFront;
                nextState = RideLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case AlignFront: // State: drive forward and align with the front tape.
            ThisEvent = RunAlignTapeSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    printf("TRAVERSEFIELD-ALIGNFRONT-ESENTRY\n");
                    ES_Timer_StopTimer(BACKWARD_TIMER);
                    break;
                case TAPE_ALIGNED:
                    //                    printf("ALIGNFRONT-TAPEALIGNED\n");

                    PS_Stop();
                    PS_Backward(700);
                    ES_Timer_InitTimer(BACKWARD_TIMER, ALINGFRONT_BACKWARD_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case BACKWARD_TIMER:
                            //                            printf("ALIGNFRONT-BACKWARD_TIMER\n");
                            PS_Stop();

                            PS_TankTurnRight(FRONTTORIGHT_TURNRIGHT_SPEED);
                            ES_Timer_InitTimer(TURNRIGHT_TIMER, FRONTTORIGHT_TURNRIGHT_TIMER);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case TURNRIGHT_TIMER:
                            //                            printf("ALIGNFRONT-TURNRIGHT_TIMER\n");
                            PS_Stop();
                            nextState = RideFront;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                        default:
                            break;
                    }
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case RideFront: // State: ride along the front tape until the right border is found.
            ThisEvent = RunRideFrontSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    break;
                case RIGHT_BORDER_FOUND:
                    printf("right border found\n");

                    PS_Backward(700);
                    ES_Timer_InitTimer(BACKWARD_TIMER, ALINGFRONT_BACKWARD_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;



                    break;
                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case BACKWARD_TIMER:
                            PS_Stop();
                            //                            printf("TRAVERSEFIELD-RIDEFRONT-ESTIMEOUT-BACKWARDTIMER");
                            PS_TankTurnRight(RIGHTTOISZ_TURNRIGHT_SPEED);
                            ES_Timer_InitTimer(TURNRIGHT_TIMER, RIGHTTOISZ_TURNRIGHT_TIMER);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case TURNRIGHT_TIMER:
                            //                            printf("TRAVERSEFIELD-RIDEFRONT-ESTIMEOUT-TURNRIGHTTIMER");
                            PS_Stop();
                            nextState = RideRight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        default:
                            break;
                    }
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case RideRight: // State: ride along the right tape toward the ISZ.
            //            printf("RUNNING: RUNRIDERIGHTSUBHSM\n");
            ThisEvent = RunRideRightSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case ES_ENTRY:

                    break;
                case BUMPER_TRIPPED:
                    PS_Stop();
                    nextState = AvoidRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case AlignLeft: // State: after avoiding from the right, align with the left-side tape.
            //                        printf("RUNNING: RUNALIGNTAPESUBHSM\n");


            ThisEvent = RunAlignTapeSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_StopTimer(BACKWARD_TIMER);
                    break;
                case TAPE_ALIGNED:

                    printf("align left tape aligmed\n");
                    PS_Stop();
                    PS_Backward(700);

                    ES_Timer_InitTimer(BACKWARD_TIMER, ALINGLEFT_BACKWARD_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case BACKWARD_TIMER:
                            PS_Stop();
                            PS_TankTurnLeft(RIGHTTOLEFT_TURNRIGHT_SPEED);
                            ES_Timer_InitTimer(TURNLEFT_TIMER, RIGHTTOLEFT_TURNRIGHT_TIMER);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case TURNLEFT_TIMER:
                            PS_Stop();
                            nextState = RideLeft;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        default:
                            break;
                    }
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case RideLeft: // State: ride along the left tape toward the ISZ.
            //            printf("RUNNING: RUNRIDELEFTSUBHSM\n");
            ThisEvent = RunRideLeftSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    printf("TRAVERSEFIELD-RIDELEFT-ESENTRY\n");
                    break;
                case BUMPER_TRIPPED:
                    PS_Stop();
                    nextState = AvoidLeft;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case AlignRight: // State: after avoiding from the left, align with the right-side tape.
            //            printf("RUNNING: RUNALIGNTAPESUBHSM\n");

            ThisEvent = RunAlignTapeSubHSM(ThisEvent);

            switch (ThisEvent.EventType) {
                case TAPE_ALIGNED:
                    printf("align right tape aligmed\n");
                    PS_Backward(700);
                    ES_Timer_InitTimer(BACKWARD_TIMER, ALINGRIGHT_BACKWARD_TIME);
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case BACKWARD_TIMER:
                            PS_Stop();
                            PS_TankTurnRight(LEFTTORIGHT_TURNRIGHT_SPEED);
                            ES_Timer_InitTimer(TURNRIGHT_TIMER, LEFTTORIGHT_TURNRIGHT_TIMER);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case TURNRIGHT_TIMER:
                            PS_Stop();
                            nextState = RideRight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        default:
                            break;
                    }
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;



        case AvoidRight: //avoid coming from the right border

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    PS_Backward(AVOIDRIGHT_BACKWARD_SPEED);
                    ES_Timer_InitTimer(BACKWARD_TIMER, AVOIDRIGHT_BACKWARD_TIME);
                    ES_Timer_StopTimer(TURNRIGHT_TIMER);
                    ES_Timer_StopTimer(TURNLEFT_TIMER);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case BACKWARD_TIMER:
                            printf("Finished avoid right backward\n");
                            PS_Stop();
                            PS_TankTurnRight(AVOIDRIGHT_TURNRIGHT_SPEED);
                            ES_Timer_InitTimer(TURNRIGHT_TIMER, AVOIDRIGHT_TURNRIGHT_TIME);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case TURNRIGHT_TIMER:
                            printf("Finished avoid right turnright\n");
                            PS_Forward(AVOIDRIGHT_FORWARD_SPEED);
                            ES_Timer_InitTimer(FORWARD_TIMER, AVOIDRIGHT_FORWARD_TIME);
                            break;
                        case FORWARD_TIMER:
                            printf("Finished avoid right forward\n");
                            PS_Stop();
                            nextState = AlignLeft;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;

        case AvoidLeft:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    PS_Backward(AVOIDLEFT_BACKWARD_SPEED);
                    ES_Timer_InitTimer(BACKWARD_TIMER, AVOIDLEFT_BACKWARD_TIME);

                    ES_Timer_StopTimer(TURNRIGHT_TIMER);
                    ES_Timer_StopTimer(TURNLEFT_TIMER);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {

                        case BACKWARD_TIMER:
                            PS_Stop();
                            printf("Finished avoid left backward\n");
                            PS_TankTurnLeft(AVOIDLEFT_TURNLEFT_SPEED);
                            ES_Timer_InitTimer(TURNLEFT_TIMER,
                                    AVOIDLEFT_TURNLEFT_TIME);

                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                        case TURNLEFT_TIMER:
                            printf("Finished avoid left turneleft\n");
                            PS_Stop();
                            PS_Forward(AVOIDLEFT_FORWARD_SPEED);
                            ES_Timer_InitTimer(FORWARD_TIMER,
                                    AVOIDLEFT_FORWARD_TIME);

                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                        case FORWARD_TIMER:
                            PS_Stop();
                            printf("Finished avoid left forwards\n");

                            nextState = AlignRight;
                            makeTransition = TRUE;

                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                    }
                    break;

                default:
                    break;
            }
            break;
        case Stop: // State: stop here for debugging.
            while (1) {
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTraverseFieldSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        ThisEvent = RunTraverseFieldSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
