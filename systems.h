/*
 * systems.h
 *
 *  Created on: Oct 28, 2016
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

//lift functions and constants
#define DEFAULT_LIFT_SPEED 67
void initializeLiftSystemThread(void);
void setLiftSpeeds(int16_t);

#endif /* SYSTEMS_H_ */
