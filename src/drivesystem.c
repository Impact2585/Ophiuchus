/*
 * drivesystem.c
 *
 *  Created on: Oct 28, 2016
 *      Author: fibbonacci
 */
#include "../ports.h"
#include "../systems.h"
#include "vex.h"
#include "ch.h"

static char* TASK_NAME = "drive";

//the task to be run
void runDriveSystem() {
	int16_t yAxis = vexControllerGet(Y_AXIS);
	int16_t xAxis = vexControllerGet(X_AXIS);

	motorDriveControlRight(yAxis + xAxis);
	motorDriveControlLeft(yAxis - xAxis);
	setSwerveMotorSpeed(xAxis);
}

static WORKING_AREA(waDriveTask, DEFAULT_WA_SIZE);

//the drive task thread
static msg_t driveSystemThread(void* arg) {
	(void)arg;
	vexTaskRegister(TASK_NAME);
	while(1) {
		runDriveSystem();
		vexSleep(25);
	}
	return (msg_t)0;
}

//creates the drive task thread
void initializeDriveSystemThread(void) {
	chThdCreateStatic(waDriveTask, sizeof(waDriveTask), NORMALPRIO - 1, driveSystemThread, NULL);
}

//set the speed of the left drivetrain motors
void motorDriveControlLeft(int16_t speed) {
	vexMotorSet( MOTOR_DRIVE_LEFT_FRONT, -speed);
	vexMotorSet( MOTOR_DRIVE_LEFT_BEHIND, -speed);
}

//set the speed of the right drivetrain motors
void motorDriveControlRight(int16_t speed) {
	vexMotorSet( MOTOR_DRIVE_RIGHT_FRONT, -speed);
	vexMotorSet( MOTOR_DRIVE_RIGHT_BEHIND, -speed);
}

//sets the speed of the swerve motors
void setSwerveMotorSpeed(int16_t speed) {
	vexMotorPositionSet(MOTOR_DRIVETRAIN_SWERVE, speed);
}
