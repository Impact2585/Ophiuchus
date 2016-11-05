/*
 * shootersystem.c
 */
#include "../systems.h"
#include "../ports.h"
#include <stdlib.h>

static char* SHOOT_TASK_NAME = "shoot";

//the lift task to run
void runShootTask(void) {
	int16_t shouldShoot = vexControllerGet(SHOOT);

	//moves forward then back
	if(shouldShoot) {
		timedShoot();
	}
}

//use timed shoot
void timedShoot(void) {
	setShootSpeeds(DEFAULT_SHOOTER_SPEED);
	vexSleep(SHOOT_TIME);
	setShootSpeeds(-DEFAULT_SHOOTER_SPEED);
	vexSleep(SHOOT_TIME);
	setShootSpeeds(0);
}

//use encoder values to shoot
void encoderShoot(void) {
	rotateTowardsDegrees(100);
	rotateTowardsDegrees(-100);
}

//default working area of the thread size is 512 bytes
static WORKING_AREA(waLiftTask, DEFAULT_WA_SIZE);

//the lift task thread
static msg_t shootTask(void* arg) {
	(void)arg;
	vexTaskRegister(SHOOT_TASK_NAME);
	while(1) {
		//runs the shooter task
		runShootTask();

		//don't hog cpu
		vexSleep(25);
	}
	return (msg_t)0;
}

//creates a thread that runs the lift task
void initializeShootSystemThread(void) {
	chThdCreateStatic(waLiftTask, sizeof(waLiftTask), NORMALPRIO - 1, shootTask, NULL);
}

//sets the lift speeds
void setShootSpeeds(int16_t speed) {
	vexMotorSet(SHOOTER_MOTOR_1, -speed);
	vexMotorSet(SHOOTER_MOTOR_2, speed);
}

//get the shooter encoder's count
int32_t getShooterEncoderValue(void) {
	return vexEncoderGet(getShooterEncoderID());
}

//gets the ID of the shooter encoder
int16_t getShooterEncoderID(void) {
	return vexMotorEncoderIdGet(SHOOTER_MOTOR_1);
}

//rotate towards degrees
void rotateTowardsDegrees(int32_t degrees) {
	//starts the encoder
	vexEncoderStart(getShooterEncoderID());
	while(abs(getShooterEncoderValue()) < abs(degrees)) {
		setShootSpeeds(sign(degrees)* DEFAULT_SHOOTER_SPEED);
	}
	//sets the motor speeds back to 0
	setShootSpeeds(0);
	//sets the encoder value back to 0
	vexEncoderSet(getShooterEncoderID(), 0);
}
