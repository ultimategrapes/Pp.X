#include <Movement.h>
#include <BOARD.h>
#include <xc.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include <IO_Ports.h>

//motors
#define LEFT_PWM PWM_PORTY10
#define RIGHT_PWM PWM_PORTY12
#define LEFT_IN1 PORTY06_LAT
#define LEFT_IN2 PORTY05_LAT
#define RIGHT_IN1 PORTY08_LAT
#define RIGHT_IN2 PORTY07_LAT
#define LEFT_IN1_TRIS PORTY06_TRIS
#define LEFT_IN2_TRIS PORTY05_TRIS
#define RIGHT_IN1_TRIS PORTY08_TRIS
#define RIGHT_IN2_TRIS PORTY07_TRIS

#define SWITCH_SENSOR PORTW04_BIT

#define LEFT_TAPE  PORTW03_BIT
#define MID_TAPE   PORTW06_BIT
#define RIGHT_TAPE PORTW05_BIT


#define PS_NOMINAL_BATTERY_VOLTAGE 310
#define PS_MIN_BATTERY_COMP_VOLTAGE 263

#define LEFT_MTR_OFFSET 1
#define RIGHT_MTR_OFFSET 1.11

#define MAX_SPEED 100


static unsigned int PS_CompensateDutyForBattery(unsigned int dutyCycle) {
    unsigned int batteryVoltage = PS_BatteryVoltage();
    unsigned long compensatedDuty;

    if (batteryVoltage < PS_MIN_BATTERY_COMP_VOLTAGE) {
        batteryVoltage = PS_MIN_BATTERY_COMP_VOLTAGE;
    }

    compensatedDuty = ((unsigned long) dutyCycle * PS_NOMINAL_BATTERY_VOLTAGE)
            / batteryVoltage;

    if (compensatedDuty > MAX_PWM) {
        compensatedDuty = MAX_PWM;
    }

    return (unsigned int) compensatedDuty;
}

char RawLeftMotor(int speed){
    return PWM_SetDutyCycle(LEFT_PWM, speed);
}
char RawRightMotor(int speed){
    return PWM_SetDutyCycle(RIGHT_PWM, speed);
}













static char PS_SetLeftMotor(unsigned int speed, unsigned char reverse) {
    unsigned int dutyCycle;
    speed *= LEFT_MTR_OFFSET;

    if (speed > PEASHOOTER_MAX_SPEED) {
        return ERROR;
    }

    if (speed == 0) {
        LEFT_IN1 = 0;
        LEFT_IN2 = 0;
        return PWM_SetDutyCycle(LEFT_PWM, 0);
    }

    if (reverse) {
        LEFT_IN1 = 1;
        LEFT_IN2 = 0;
    } else {
        LEFT_IN1 = 0;
        LEFT_IN2 = 1;
    }

    dutyCycle = speed * (MAX_PWM / PEASHOOTER_MAX_SPEED);
    dutyCycle = PS_CompensateDutyForBattery(dutyCycle);
    return PWM_SetDutyCycle(LEFT_PWM, dutyCycle);
}

static char PS_SetRightMotor(unsigned int speed, unsigned char reverse) {
    speed *= RIGHT_MTR_OFFSET;
    unsigned int dutyCycle;

    if (speed > PEASHOOTER_MAX_SPEED) {
        return ERROR;
    }

    if (speed == 0) {
        RIGHT_IN1 = 0;
        RIGHT_IN2 = 0;
        return PWM_SetDutyCycle(RIGHT_PWM, 0);
    }

    if (reverse) {
        RIGHT_IN1 = 1;
        RIGHT_IN2 = 0;
    } else {
        RIGHT_IN1 = 0;
        RIGHT_IN2 = 1;
    }

    dutyCycle = speed * (MAX_PWM / PEASHOOTER_MAX_SPEED);
    dutyCycle = PS_CompensateDutyForBattery(dutyCycle);
    return PWM_SetDutyCycle(RIGHT_PWM, dutyCycle);
}

void PS_LeftMotorInit(void) {
    PWM_AddPins(LEFT_PWM);
    LEFT_IN1_TRIS = 0;
    LEFT_IN2_TRIS = 0;
    LEFT_IN1 = 1;
    LEFT_IN2 = 0;
    PWM_SetDutyCycle(LEFT_PWM, 0);
}
void PS_RightMotorInit(void) {
    PWM_AddPins(RIGHT_PWM);

    RIGHT_IN1_TRIS = 0;
    RIGHT_IN2_TRIS = 0;

    RIGHT_IN1 = 1;
    RIGHT_IN2 = 0;

    PWM_SetDutyCycle(RIGHT_PWM, 0);
}

void PS_IndexerMotorInit(void) {
}

void PS_Init(void) {
    PWM_Init();

    PWM_SetFrequency(1000);

    PS_LeftMotorInit();
    PS_RightMotorInit();
    PS_IndexerMotorInit();

    PORTW03_TRIS = 1;
    PORTW04_TRIS = 1;
    PORTW05_TRIS = 1;
    PORTW06_TRIS = 1;
}

unsigned int PS_BatteryVoltage(void) {
    return AD_ReadADPin(BAT_VOLTAGE);
}

char PS_LeftMtrSpeed(unsigned int power) {
    return PS_SetLeftMotor(power, 0);
}

char PS_LeftMtrReverseSpeed(unsigned int power) {
    return PS_SetLeftMotor(power, 1);
}

char PS_RightMtrSpeed(unsigned int power) {
    return PS_SetRightMotor(power, 0);
}

char PS_RightMtrReverseSpeed(unsigned int power) {
    return PS_SetRightMotor(power, 1);
}

char PS_RawMotor(unsigned int power) {
    char leftResult;
    char rightResult;

    if (power > MAX_PWM) {
        return ERROR;
    }

    if (power == 0) {
        LEFT_IN1 = 0;
        LEFT_IN2 = 0;
        RIGHT_IN1 = 0;
        RIGHT_IN2 = 0;

        leftResult = PWM_SetDutyCycle(LEFT_PWM, 0);
        rightResult = PWM_SetDutyCycle(RIGHT_PWM, 0);
        return ((leftResult == ERROR) || (rightResult == ERROR)) ? ERROR : SUCCESS;
    }

    LEFT_IN1 = 1;
    LEFT_IN2 = 0;
    RIGHT_IN1 = 1;
    RIGHT_IN2 = 0;

    leftResult = PWM_SetDutyCycle(LEFT_PWM, power);
    rightResult = PWM_SetDutyCycle(RIGHT_PWM, power);
    return ((leftResult == ERROR) || (rightResult == ERROR)) ? ERROR : SUCCESS;
}

unsigned char PS_ReadSwitch(void) {
    return SWITCH_SENSOR ? SWITCH_NOT_TRIPPED : SWITCH_TRIPPED;
}


unsigned char PS_ReadLeftTape(void) {
    return LEFT_TAPE ? TAPE_DETECTED : TAPE_NOT_DETECTED;
}

unsigned char PS_ReadMidTape(void) {
    return MID_TAPE ? TAPE_DETECTED : TAPE_NOT_DETECTED;
}

unsigned char PS_ReadRightTape(void) {
    return RIGHT_TAPE ? TAPE_DETECTED : TAPE_NOT_DETECTED;
}

unsigned char PS_ReadTape(void) {
    return (PS_ReadLeftTape()
            + (PS_ReadMidTape() << 1)
            + (PS_ReadRightTape() << 2));
}
