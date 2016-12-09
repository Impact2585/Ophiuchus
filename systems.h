/*
 * systems.h
 */

#ifndef SYSTEMS_H_
#define SYSTEMS_H_
#include "ch.h"  		// needs for all ChibiOS programs
#include "hal.h" 		// hardware abstraction layer header
#include "vex.h"		// vex library header

#define DEFAULT_WA_SIZE 512

//input
#define Y_AXIS Ch3
#define X_AXIS Ch1

#define SHOOT Btn8U
#define MANUAL_SHOOT_FORWARD Btn6U
#define MANUAL_SHOOT_BACKWARD Btn6D

#define OPEN_CLAW Btn8R
#define CLOSE_CLAW Btn8D

#define OPEN_CLAW_LEFT Btn7U
#define CLOSE_CLAW_LEFT Btn7R

#define OPEN_CLAW_RIGHT Btn7L
#define CLOSE_CLAW_RIGHT Btn7D

#define LOCK Btn5D
#define UNLOCK Btn5U

#define LIFT_BACK Btn5D
#define LIFT_FOWARD Btn5U

//drive functions and constants
#define DEADZONE 30 
struct driveSystem {
	int16_t yAxis;
	int16_t xAxis;
	int16_t reversedMode;
	int8_t prevToggle;
	int16_t leftSpeed;
	int16_t rightSpeed;
};
void motorDriveControlLeft(int16_t speed);
void motorDriveControlRight(int16_t speed);
void runDriveSystem(struct driveSystem* drivetrain);
void initializeDriveSystemThread(void);
void initializeDriveSystem(struct driveSystem* drivetrain);
void setDriveTrainDeadZone(struct driveSystem* drivetrain);
void calculateDriveSystemSpeed(struct driveSystem* drivetrain);
void setReversed(struct driveSystem* drivetrain);



//shooter functions and constants
#define DEFAULT_SHOOTER_SPEED 100
struct shootInfo {
	int16_t forwardShoot;
	int16_t backShoot;
	int16_t shouldShoot;
	int8_t isLocked;
	int8_t releaseLock;
	int8_t lock;
	int8_t unlock;
};

//initializes all values of the shootInfo struct to 0
#define INIT_SHOOTER(shooter) struct shootInfo shooter = {\
	.forwardShoot = 0,\
	.backShoot = 0,\
	.shouldShoot = 0,\
	.isLocked = 0,\
	.releaseLock = 0,\
	.lock = 0,\
	.unlock = 0\
}

void releaseLock(void);
void initializeShootSystemThread(void);
void setShootSpeed(int16_t speed);
void rotateTowardsDegrees(int32_t degrees);
int16_t getShooterEncoderID(void);
int32_t getShooterEncoderValue(void);
void getShooterInput(struct shootInfo *shooter);

// lift functions and constants
#define DEFAULT_LIFT_SPEED 67
void runLiftTask(void);
void initializeLiftSystemThread(void);
void setLiftSpeed(int16_t speed);
void primeForShooting(void);
void encoderShoot(void);

//claw functions and constants
#define CLAW_SPEED 40
void moveClaw(int16_t open);
void initializeClawSystemThread(void);
void setClawSpeed(int16_t open);

//auton functions and constants
#define AUTON_DRIVE_SPEED 67
void driveAndShootAuton(void);

//get sign of number for all types
#define sign(x) ((x > 0) - (x < 0))

#endif 
/* SYSTEMS_H_ */
