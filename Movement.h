#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <BOARD.h>

// Switch sensor return states.
#define SWITCH_TRIPPED 1
#define SWITCH_NOT_TRIPPED 0

// Tape sensor return states.
#define TAPE_DETECTED 1
#define TAPE_NOT_DETECTED 0

// Analog thresholds used to classify switch and tape sensor readings.
#define TAPE_HIGH 900
#define TAPE_LOW  200
#define SWITCH_THRESHOLD 2

// Bit positions used when packing the three tape sensors into one byte.
#define LEFT_TAPE_MASK  (1)
#define MID_TAPE_MASK   (1 << 1)
#define RIGHT_TAPE_MASK (1 << 2)


// Maximum motor command accepted by the peashooter speed functions.
#define PEASHOOTER_MAX_SPEED 1000 

// Blocking delay calibration constants for distance and turn helper functions.
#define MOVE_TIME_PER_DIST 50000

#define TURN_LEFT_TIME  800000
#define TURN_RIGHT_TIME 800000
#define TURN_90_TIME 600000

// Busy-wait delay macro used by the turn helper functions.
#define DELAY_COUNTS(x) for(delay = 0; delay < (x); delay++) {asm("nop");}

// Initializes peashooter motors, PWM, tape sensor inputs, and ADC channels.
void PS_Init(void);

// Returns the raw 10-bit ADC reading for the battery voltage monitor.
unsigned int PS_BatteryVoltage(void);

char RawRightMotor(int speed);
char RawLeftMotor(int speed);
#endif
