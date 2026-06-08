/*
 * File: FindBeaconSubHSM.c
 *
 * Beacon detection ported from HSM.X (HSMService.c / BeaconEventChecker.c).
 *
 * Instead of a continuous 360 sweep that tracks a peak, this uses HSM.X's
 * incremental "stepped" tank turn: drive briefly with the motors on, then brake
 * and hold. Beacon ADC samples are only trusted during the motors-off hold,
 * after the base has had time to settle, and a lock is only declared after a
 * few consecutive above-threshold samples. This keeps motor noise from
 * producing a false detection at the wrong orientation.
 */

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "MainHSM.h"
#include "FindBeaconSubHSM.h"
#include "peashooter.h"
#include <stdio.h>

/* --- Beacon detection tuning (mirrors HSM.X HSMService.c) --- */

/* A sample only counts as a detection above this raw ADC threshold. */
#define BEACON_DETECT_MIN           700   /* HSM_BEACON_DETECT_MIN */

/* Consecutive motors-off detections required to confirm a lock. A single
 * sample crossing the threshold can be a transient spike or a reflection at the
 * wrong orientation; requiring a sustained reading aligns the lock with the
 * true beacon direction. The count resets on any below-threshold sample and
 * whenever the base starts moving again. */
#define BEACON_CONFIRM_COUNT        2     /* HSM_BEACON_CONFIRM_COUNT */

/* Stepped tank turn: drive briefly, then brake and hold. Sampling is only armed
 * during the motors-off hold. Right motor forward + left motor reverse matches
 * HSM.X StartLockOnStepDrive(). */
#define BEACON_TURN_POWER           700   /* HSM_LOCK_TURN_POWER */
#define BEACON_STEP_DRIVE_TIME      80    /* HSM_LOCK_STEP_DRIVE_TIME_MS */
#define BEACON_STEP_PAUSE_TIME      250   /* HSM_LOCK_STEP_PAUSE_TIME_MS */

/* Time the base needs to coast to a stop after motors off before a beacon
 * sample is trustworthy. Also the delay before the first armed sample of each
 * hold. HSM.X brakes actively; this base only coasts (PS_Stop), so the settle
 * window is what keeps motor-spin noise out of the reading. */
#define BEACON_SETTLE_TIME          80    /* HSM_BEACON_SETTLE_MS */

/* Cadence of the remaining armed samples taken during a single hold. */
#define BEACON_SAMPLE_INTERVAL      30

#define BEACON_STEP_TIMER           SWEEP_TIMER   /* drive/hold phase timing */
#define BEACON_SAMPLE_TIMER         SAMPLE_TIMER  /* armed sample cadence */

typedef enum {
    InitPSubState,
    LockToBeacon,
    BeaconFound,
} FindBeaconSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "LockToBeacon",
    "BeaconFound",
};

static FindBeaconSubHSMState_t CurrentState = InitPSubState;
static uint8_t StepDriving = FALSE;
static uint8_t BeaconDetectCount = 0;
static uint16_t BeaconPeakValue = 0;

static void StartBeaconStepDrive(void);
static void StartBeaconStepPause(void);
static uint8_t BeaconSampleIsDetected(uint16_t adcReading);
static uint8_t CheckBeaconLock(void);

uint8_t InitFindBeaconSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    StepDriving = FALSE;
    BeaconDetectCount = 0;
    BeaconPeakValue = 0;

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
                nextState = LockToBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case LockToBeacon:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    StartBeaconStepDrive();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == BEACON_STEP_TIMER) {
                        /* One increment of the stepped turn finished. */
                        if (StepDriving == TRUE) {
                            StartBeaconStepPause();
                        } else {
                            /* Hold ended with no confirmed lock: keep turning. */
                            StartBeaconStepDrive();
                        }
                        ThisEvent.EventType = ES_NO_EVENT;

                    } else if (ThisEvent.EventParam == BEACON_SAMPLE_TIMER) {
                        /* Armed sample. Readings taken while the motors are
                         * running are ignored so motor noise cannot complete a
                         * lock during the step drive. */
                        if (StepDriving == FALSE) {
                            if (CheckBeaconLock() == TRUE) {
                                nextState = BeaconFound;
                                makeTransition = TRUE;
                            } else {
                                ES_Timer_InitTimer(BEACON_SAMPLE_TIMER,
                                                   BEACON_SAMPLE_INTERVAL);
                            }
                        }
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_EXIT:
                    ES_Timer_StopTimer(BEACON_STEP_TIMER);
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
                    ES_Timer_StopTimer(BEACON_STEP_TIMER);
                    ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);
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

/* One increment of the stepped tank turn: drive briefly with the motors on.
 * Samples taken now are corrupted by motor noise, so sampling is disarmed and
 * the detection count is cleared so confirmation must accumulate within one
 * stationary hold. */
static void StartBeaconStepDrive(void)
{
    StepDriving = TRUE;
    BeaconDetectCount = 0;

    ES_Timer_StopTimer(BEACON_SAMPLE_TIMER);

    PS_RightMtrSpeed(BEACON_TURN_POWER);
    PS_LeftMtrReverseSpeed(BEACON_TURN_POWER);

    ES_Timer_InitTimer(BEACON_STEP_TIMER, BEACON_STEP_DRIVE_TIME);
}

/* Stop and hold so the beacon can be sampled without motor noise. The step
 * timer bounds the hold; the sample timer fires the first armed sample only
 * after the settle time so the still-spinning motors cannot corrupt it. */
static void StartBeaconStepPause(void)
{
    StepDriving = FALSE;
    BeaconDetectCount = 0;

    PS_Stop();

    ES_Timer_InitTimer(BEACON_STEP_TIMER, BEACON_STEP_PAUSE_TIME);
    ES_Timer_InitTimer(BEACON_SAMPLE_TIMER, BEACON_SETTLE_TIME);
}

static uint8_t BeaconSampleIsDetected(uint16_t adcReading)
{
    return (adcReading > BEACON_DETECT_MIN) ? TRUE : FALSE;
}

/* Mirrors HSM_CheckBeaconLockImmediate: require BEACON_CONFIRM_COUNT
 * consecutive above-threshold samples within one stationary hold. Any
 * below-threshold sample resets the count. Returns TRUE on a confirmed lock. */
static uint8_t CheckBeaconLock(void)
{
    uint16_t beaconReading = (uint16_t) PS_ReadBeacon();

    printf("Beacon lock sample=%u count=%u\n", beaconReading, BeaconDetectCount);

    if (BeaconSampleIsDetected(beaconReading) != TRUE) {
        BeaconDetectCount = 0;
        return FALSE;
    }

    if (BeaconDetectCount < BEACON_CONFIRM_COUNT) {
        BeaconDetectCount++;
    }

    if (BeaconDetectCount < BEACON_CONFIRM_COUNT) {
        return FALSE;
    }

    BeaconDetectCount = 0;
    StepDriving = FALSE;
    BeaconPeakValue = beaconReading;
    PS_Stop();

    printf("Beacon locked: sample=%u\n", beaconReading);
    return TRUE;
}
