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
#define SHOOT Btn6U

//drive functions
void motorDriveControlLeft(int16_t speed);
void motorDriveControlRight(int16_t speed);
void setSwerveMotorSpeed(int16_t speed);
void runDriveSystem(void);
void initializeDriveSystemThread(void);

//shooter functions and constants
#define DEFAULT_SHOOTER_SPEED 20
void initializeShootSystemThread(void);
void setShootSpeeds(int16_t);
void rotateTowardsDegrees(int32_t degrees);
int16_t getShooterEncoderID(void);
int32_t getShooterEncoderValue(void);


//get sign of number for all types
#define sign(x) ((x > 0) - (x < 0))

#endif /* SYSTEMS_H_ */
