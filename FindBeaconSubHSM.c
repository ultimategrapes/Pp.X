/*
 * File: FindBeaconSubHSM.c
 */

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "MainHSM.h"
#include "FindBeaconSubHSM.h"
#include "peashooter.h"
#include <stdio.h>

#define BEACON_MIN_VALID_PEAK 800
#define BEACON_SWEEP_SPEED          700
#define BEACON_SWEEP_360_TIME       4400
#define BEACON_PEAK_TOLERANCE       30
#define BEACON_LOCK_COUNT_REQUIRED  2

#define BEACON_SAMPLE_TIMER         SAMPLE_TIMER
#define BEACON_SAMPLE_TIME          50

typedef enum {
    InitPSubState,
    SweepBeacon,
    LockToBeacon,
    BeaconFound,
} FindBeaconSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "SweepBeacon",
    "LockToBeacon",
    "BeaconFound",
};

static FindBeaconSubHSMState_t CurrentState = InitPSubState;
static uint16_t BeaconPeakValue = 0;
static uint8_t BeaconLockCount = 0;

static void StartBeaconSweep360(void);
static void UpdateBeaconSweepMax(void);
static uint16_t FinishBeaconSweep360(void);
static void StartBeaconPeakLock(uint16_t peakValue);
static uint8_t CheckBeaconPeakLock(void);

uint8_t InitFindBeaconSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    BeaconPeakValue = 0;
    BeaconLockCount = 0;

    returnEvent = RunFindBeaconSubHSM(INIT_EVENT);

    return (returnEvent.EventType == ES_NO_EVENT);
}

ES_Event RunFindBeaconSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    FindBeaconSubHSMState_t nextState = CurrentState;

    ES_Tattle();

    switch (CurrentState) {

        case InitPSubState:
            if (ThisEvent.EventType == ES_INIT) {
                nextState = SweepBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case SweepBeacon:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    StartBeaconSweep360();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == BEACON_SAMPLE_TIMER) {
                        UpdateBeaconSweepMax();
                        ES_Timer_InitTimer(BEACON_SAMPLE_TIMER,
                                           BEACON_SAMPLE_TIME);
                        ThisEvent.EventType = ES_NO_EVENT;

                    } else if (ThisEvent.EventParam == SWEEP_TIMER) {
    BeaconPeakValue = FinishBeaconSweep360();

    if (BeaconPeakValue >= BEACON_MIN_VALID_PEAK) {
        nextState = LockToBeacon;
    } else {
        printf("Beacon peak too low: %u, sweeping again\n", BeaconPeakValue);
        nextState = SweepBeacon;
    }

    makeTransition = TRUE;
    ThisEvent.EventType = ES_NO_EVENT;
}
                    break;

                case ES_EXIT:
                    ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);
                    PS_Stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case LockToBeacon:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    StartBeaconPeakLock(BeaconPeakValue);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == BEACON_SAMPLE_TIMER) {

                        if (CheckBeaconPeakLock() == TRUE) {
                            nextState = BeaconFound;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ES_Timer_InitTimer(BEACON_SAMPLE_TIMER,
                                               BEACON_SAMPLE_TIME);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }

                    } else if (ThisEvent.EventParam == SWEEP_TIMER) {
                        PS_Stop();

                        nextState = SweepBeacon;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_EXIT:
                    ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);
                    PS_Stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case BeaconFound:
    switch (ThisEvent.EventType) {

        case ES_ENTRY:
            ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);
            ES_Timer_StopTimer(SWEEP_TIMER);
            PS_Stop();

            ThisEvent.EventType = BEACON_DETECTED;
            ThisEvent.EventParam = BeaconPeakValue;
            break;

        case ES_EXIT:
            ThisEvent.EventType = ES_NO_EVENT;
            break;

        default:
            ThisEvent.EventType = ES_NO_EVENT;
            break;
    }
    break;

        default:
            break;
    }

    if (makeTransition == TRUE) {
        RunFindBeaconSubHSM(EXIT_EVENT);
        CurrentState = nextState;
        ThisEvent = RunFindBeaconSubHSM(ENTRY_EVENT);
    }

    ES_Tail();
    return ThisEvent;
}

static void StartBeaconSweep360(void)
{
    BeaconPeakValue = 0;
    BeaconLockCount = 0;

    PS_TankTurnRightContinuous(BEACON_SWEEP_SPEED);

    ES_Timer_InitTimer(SWEEP_TIMER, BEACON_SWEEP_360_TIME);
    ES_Timer_InitTimer(BEACON_SAMPLE_TIMER, BEACON_SAMPLE_TIME);
}

static void UpdateBeaconSweepMax(void)
{
    uint16_t beaconReading;

    beaconReading = PS_ReadBeacon();

    printf("Beacon sweep sample: %u\n", beaconReading);

    if (beaconReading > BeaconPeakValue) {
        BeaconPeakValue = beaconReading;
    }

    printf("Beacon sweep processed: sample=%u peak=%u\n",
           beaconReading,
           BeaconPeakValue);
}

static uint16_t FinishBeaconSweep360(void)
{
    ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);
    PS_Stop();

    printf("Beacon sweep finished: peak=%u\n", BeaconPeakValue);

    return BeaconPeakValue;
}

static void StartBeaconPeakLock(uint16_t peakValue)
{
    BeaconPeakValue = peakValue;
    BeaconLockCount = 0;

    printf("Beacon lock start: peak=%u target=%u\n",
           BeaconPeakValue,
           (BeaconPeakValue > BEACON_PEAK_TOLERANCE)
               ? (BeaconPeakValue - BEACON_PEAK_TOLERANCE)
               : 0);

    PS_TankTurnRightContinuous(BEACON_SWEEP_SPEED);

    ES_Timer_InitTimer(SWEEP_TIMER, BEACON_SWEEP_360_TIME);
    ES_Timer_InitTimer(BEACON_SAMPLE_TIMER, BEACON_SAMPLE_TIME);
}

static uint8_t CheckBeaconPeakLock(void)
{
    uint16_t beaconReading;
    uint16_t target;

    beaconReading = PS_ReadBeacon();

    if (BeaconPeakValue > BEACON_PEAK_TOLERANCE) {
        target = BeaconPeakValue - BEACON_PEAK_TOLERANCE;
    } else {
        target = 0;
    }

    printf("Beacon lock sample=%u target=%u count=%u\n",
           beaconReading,
           target,
           BeaconLockCount);

    if (beaconReading >= target) {
        BeaconLockCount++;

        if (BeaconLockCount >= BEACON_LOCK_COUNT_REQUIRED) {
            PS_Stop();
            ES_Timer_StopTimer(SWEEP_TIMER);
            ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);

            printf("Beacon locked: sample=%u peak=%u\n",
                   beaconReading,
                   BeaconPeakValue);

            return TRUE;
        }
    } else {
        BeaconLockCount = 0;
    }

    return FALSE;
}