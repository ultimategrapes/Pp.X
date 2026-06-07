#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <BOARD.h>

// Switch sensor return states.
#define SWITCH_TRIPPED 1
#define SWITCH_NOT_TRIPPED 0

// Tape sensor return states.
#define TAPE_DETECTED 1
#define TAPE_NOT_DETECTED 0

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

// Initializes the left drive motor PWM pin and direction pins.
void PS_LeftMotorInit(void);

// Initializes the right drive motor PWM pin and direction pins.
void PS_RightMotorInit(void);

// Initializes the indexer motor output.
void PS_IndexerInit(void);

// Initializes the shooter motor outputs.
void PS_ShooterInit(void);

// Returns the raw 10-bit ADC reading for the battery voltage monitor.
unsigned int PS_BatteryVoltage(void);

// Reads the switch sensor and returns SWITCH_TRIPPED or SWITCH_NOT_TRIPPED.
unsigned char PS_ReadSwitch(void);

// Reads the left tape sensor.
unsigned char PS_ReadLeftTape(void);

// Reads the middle tape sensor.
unsigned char PS_ReadMidTape(void);

// Reads the right tape sensor.
unsigned char PS_ReadRightTape(void);

// Packs left, middle, and right tape states into bits 0, 1, and 2.
unsigned char PS_ReadTape(void);

// Sets left motor forward speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_LeftMtrSpeed(unsigned int power);

// Sets left motor reverse speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_LeftMtrReverseSpeed(unsigned int power);

// Sets right motor forward speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_RightMtrSpeed(unsigned int power);

// Sets right motor reverse speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_RightMtrReverseSpeed(unsigned int power);

// Sets both motors using a raw PWM duty cycle from 0 to MAX_PWM.
char PS_RawMotor(unsigned int power);

// Drives both motors forward at the requested power.
char PS_Forward(unsigned int power);

// Drives both motors backward at the requested power.
char PS_Backward(unsigned int power);

// Stops both drive motors.
char PS_Stop(void);

// Drives forward for an approximate distance using a blocking delay.
char PS_ForwardDist(unsigned int power, char dist);

// Drives backward for an approximate distance using a blocking delay.
char PS_BackwardDist(unsigned int power, char dist);

// Spins left by driving the motors in opposite directions for a fixed delay.
char PS_TankTurnLeft(unsigned int power);

// Spins right by driving the motors in opposite directions for a fixed delay.
char PS_TankTurnRight(unsigned int power);

// Spins left for an approximate distance using a blocking delay.
char PS_TankTurnLeftDist(unsigned int power, unsigned int dist);

// Spins right for an approximate distance using a blocking delay.
char PS_TankTurnRightDist(unsigned int power, unsigned int dist);

// Spins left continuously until another motor command or PS_Stop is issued.
char PS_TankTurnLeftContinuous(unsigned int power);

// Spins right continuously until another motor command or PS_Stop is issued.
char PS_TankTurnRightContinuous(unsigned int power);

// Pivots left by stopping the left wheel and driving the right wheel.
char PS_PivotTurnLeft(unsigned int power);

// Pivots right by stopping the right wheel and driving the left wheel.
char PS_PivotTurnRight(unsigned int power);

char PS_TurnRight90(void);
char PS_TurnLeft90(void);

// Drives forward with a slight right curve.
char PS_AngledRight(unsigned int power);

// Drives forward with a slight left curve.
char PS_AngledLeft(unsigned int power);

// Returns the raw ADC reading for the beacon detector.
uint32_t PS_ReadBeacon(void);

// Sets the top shooter motor speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_SetTopShooter(unsigned int speed);

// Sets the bottom shooter motor speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_SetBotShooter(unsigned int speed);

// Sets the indexer motor speed from 0 to PEASHOOTER_MAX_SPEED.
char PS_SetIndexer(unsigned int speed);

#endif
