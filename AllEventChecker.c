/*
 * File:   TemplateEventChecker.c
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with both FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This file includes a test harness that will run the event detectors listed in the
 * ES_Configure file in the project, and will conditionally compile main if the macro
 * EVENTCHECKER_TEST is defined (either in the project or in the file). This will allow
 * you to check you event detectors in their own project, and then leave them untouched
 * for your project unless you need to alter their post functions.
 *
 * Created on September 27, 2013, 8:37 AM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "AllEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "MainHSM.h"
#include "peashooter.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 100
#define SENSOR_STATE_UNKNOWN 0xFF
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t CheckBattery(void) {
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

uint8_t CheckTape(void) {

    static unsigned char debouncedLeft = SENSOR_STATE_UNKNOWN;
    static unsigned char debouncedMiddle = SENSOR_STATE_UNKNOWN;
    static unsigned char debouncedRight = SENSOR_STATE_UNKNOWN;

    static unsigned char lastLeftSample = SENSOR_STATE_UNKNOWN;
    static unsigned char lastMiddleSample = SENSOR_STATE_UNKNOWN;
    static unsigned char lastRightSample = SENSOR_STATE_UNKNOWN;

    static unsigned char leftCount = 0;
    static unsigned char middleCount = 0;
    static unsigned char rightCount = 0;

    static uint8_t initialized = FALSE;

    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    unsigned char leftTape = PS_ReadLeftTape();
    unsigned char middleTape = PS_ReadMidTape();
    unsigned char rightTape = PS_ReadRightTape();

#define TAPE_DEBOUNCE_COUNT 20

    if (initialized == FALSE) {
        debouncedLeft = leftTape;
        debouncedMiddle = middleTape;
        debouncedRight = rightTape;

        lastLeftSample = leftTape;
        lastMiddleSample = middleTape;
        lastRightSample = rightTape;

        leftCount = 0;
        middleCount = 0;
        rightCount = 0;

        initialized = TRUE;
        return FALSE;
    }

    if (leftTape == lastLeftSample) {
        if (leftCount < TAPE_DEBOUNCE_COUNT) {
            leftCount++;
        }
    } else {
        lastLeftSample = leftTape;
        leftCount = 1;
    }

    if (middleTape == lastMiddleSample) {
        if (middleCount < TAPE_DEBOUNCE_COUNT) {
            middleCount++;
        }
    } else {
        lastMiddleSample = middleTape;
        middleCount = 1;
    }

    if (rightTape == lastRightSample) {
        if (rightCount < TAPE_DEBOUNCE_COUNT) {
            rightCount++;
        }
    } else {
        lastRightSample = rightTape;
        rightCount = 1;
    }

    if ((leftCount >= TAPE_DEBOUNCE_COUNT) && (leftTape != debouncedLeft)) {
        debouncedLeft = leftTape;
        thisEvent.EventType = (debouncedLeft == TAPE_DETECTED)
                ? LEFT_TAPE_DETECTED : LEFT_TAPE_NOT_DETECTED;
        thisEvent.EventParam = debouncedLeft;
        returnVal = TRUE;
    } else if ((middleCount >= TAPE_DEBOUNCE_COUNT) && (middleTape != debouncedMiddle)) {
        debouncedMiddle = middleTape;
        thisEvent.EventType = (debouncedMiddle == TAPE_DETECTED)
                ? MIDDLE_TAPE_DETECTED : MIDDLE_TAPE_NOT_DETECTED;
        thisEvent.EventParam = debouncedMiddle;
        returnVal = TRUE;
    } else if ((rightCount >= TAPE_DEBOUNCE_COUNT) && (rightTape != debouncedRight)) {
        debouncedRight = rightTape;
        thisEvent.EventType = (debouncedRight == TAPE_DETECTED)
                ? RIGHT_TAPE_DETECTED : RIGHT_TAPE_NOT_DETECTED;
        thisEvent.EventParam = debouncedRight;
        returnVal = TRUE;
    }

    if (returnVal == TRUE) {
#if !defined(EVENTCHECKER_TEST) && !defined(MOVEMENT_TEST)
        PostHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }

    return returnVal;
}

uint8_t CheckSwitch(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static unsigned char debouncedState = SENSOR_STATE_UNKNOWN;
    static unsigned char lastSample = SWITCH_NOT_TRIPPED;
    static unsigned char sameSampleCount = 0;
    static uint8_t initialized = FALSE;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    unsigned char switchState = PS_ReadSwitch();

    enum {
        SWITCH_DEBOUNCE_COUNT = 150
    };

    if (initialized == FALSE) {
        debouncedState = switchState;
        lastSample = switchState;
        sameSampleCount = 0;
        lastEvent = (switchState == SWITCH_TRIPPED)
                ? BUMPER_TRIPPED : BUMPER_NOT_TRIPPED;
        initialized = TRUE;
        return returnVal;
    }

    if (switchState == lastSample) {
        if (sameSampleCount < SWITCH_DEBOUNCE_COUNT) {
            sameSampleCount++;
        }
    } else {
        lastSample = switchState;
        sameSampleCount = 1;
        return returnVal;
    }

    if ((sameSampleCount >= SWITCH_DEBOUNCE_COUNT)
            && (switchState != debouncedState)) {
        debouncedState = switchState;

        if (debouncedState == SWITCH_TRIPPED) {
            curEvent = BUMPER_TRIPPED;
        } else {
            curEvent = BUMPER_NOT_TRIPPED;
        }

        if (curEvent != lastEvent) { // check for change from last time
            thisEvent.EventType = curEvent;
            thisEvent.EventParam = debouncedState;
            returnVal = TRUE;
            lastEvent = curEvent; // update history
#if !defined(EVENTCHECKER_TEST) && !defined(MOVEMENT_TEST)
            PostHSM(thisEvent);
#else
            SaveEvent(thisEvent);
#endif
        }
    }
    return (returnVal);
}

#define BEACON_HIGH_THRESHOLD 930
#define BEACON_LOW_THRESHOLD  600
#define BEACON_FILTER_SAMPLES 16

uint8_t CheckBeacon(void) {
    static ES_EventTyp_t lastEvent = BEACON_NOT_DETECTED;
    static uint16_t samples[BEACON_FILTER_SAMPLES] = {0};
    static uint8_t index = 0;
    static uint8_t filled = FALSE;
    static uint32_t sum = 0;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    uint16_t newSample = PS_ReadBeacon();

    sum -= samples[index];
    samples[index] = newSample;
    sum += newSample;

    index++;
    if (index >= BEACON_FILTER_SAMPLES) {
        index = 0;
        filled = TRUE;
    }

    if (filled == FALSE) {
        return FALSE;
    }

    uint16_t average = sum / BEACON_FILTER_SAMPLES;

    if (lastEvent == BEACON_DETECTED) {
        curEvent = (average < BEACON_LOW_THRESHOLD)
                ? BEACON_NOT_DETECTED
                : BEACON_DETECTED;
    } else {
        curEvent = (average > BEACON_HIGH_THRESHOLD)
                ? BEACON_DETECTED
                : BEACON_NOT_DETECTED;
    }

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = average;
        returnVal = TRUE;
        lastEvent = curEvent;

#if !defined(EVENTCHECKER_TEST) && !defined(MOVEMENT_TEST)
        PostHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }

    return returnVal;
}

/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */

    // Do not alter anything below this line
    int i;
printf("\r\nEvent checking test harness for %s", __FILE__);
    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }

            }
        }
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif

#ifdef MOVE_TEST

#include <stdio.h>
#define MOVING_TEST_ONE_SECOND 1000000

void main(void) {
    unsigned int delay;

    BOARD_Init();
    SERIAL_Init();
    PS_Init();
    printf("moving test\n");
    uint16_t power = 700;
    while (1) {
        PS_TankTurnRight(power);
        DELAY_COUNTS(MOVING_TEST_ONE_SECOND);
        PS_TankTurnLeft(power);
        DELAY_COUNTS(MOVING_TEST_ONE_SECOND);
    }
}


#endif
