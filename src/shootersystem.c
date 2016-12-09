/*
 * shootersystem.c
 */
#include "../systems.h"
#include "../ports.h"
#include <stdlib.h>
static char* SHOOT_TASK_NAME = "shoot";

//the lift task to run
void runShootTask(struct shootInfo *shooter) {
	//grabs input for shooter
	getShooterInput(shooter);

	//moves catapult backwards and locks it if button is pressed and the shooter isn't already locked
	if(shooter->shouldShoot && !shooter->isLocked) {
		primeForShooting();
		shooter->isLocked = 1;
	} else if(shooter->releaseLock && shooter->isLocked) {
		//releases lock and sets isLocked to 0
		releaseLock();
		shooter->isLocked = 0;
	} else {
		//manual control of the shooter
		if(shooter->forwardShoot) {
			setShootSpeed(DEFAULT_SHOOTER_SPEED);
		} else if(shooter->backShoot) {
			setShootSpeed(-DEFAULT_SHOOTER_SPEED);
		} else {
			setShootSpeed(0);
		}
		
		if(shooter->lock)
			vexDigitalPinSet(PNEUMATICS_PIN, 1);
		else if(shooter->unlock)
			vexDigitalPinSet(PNEUMATICS_PIN, 0);
	}
}

//moves the catapult backwards and locks it in place with pneumatics
void primeForShooting(void) {
	setShootSpeed(-DEFAULT_SHOOTER_SPEED);
	vexSleep(3000);
	//let Jesus and rubber bands do the rest
	setShootSpeed(0);
	//lock the pneumatics
	vexDigitalPinSet(PNEUMATICS_PIN, 1);
}

//get input for the shooter
void getShooterInput(struct shootInfo *shooter) {
	shooter->forwardShoot = vexControllerGet(MANUAL_SHOOT_FORWARD);
	shooter->backShoot = vexControllerGet(MANUAL_SHOOT_BACKWARD);
	shooter->releaseLock = vexControllerGet(Btn6U);
	shooter->shouldShoot = vexControllerGet(SHOOT);
	shooter->lock = vexControllerGet(LOCK);
	shooter->unlock = vexControllerGet(UNLOCK);
}

//release pneumatic lock
void releaseLock(void) {
	vexDigitalPinSet(PNEUMATICS_PIN, 0);
	setShootSpeed(40);
	vexSleep(500);
	setShootSpeed(0);
}

//use encoder values to shoot
void encoderShoot(void) {
	rotateTowardsDegrees(100);
	rotateTowardsDegrees(-100);
}

//default working area of the thread size is 512 bytes
static WORKING_AREA(waLiftTask, DEFAULT_WA_SIZE);

//the shoot task thread
static msg_t shootTask(void* arg) {
	(void)arg;
	INIT_SHOOTER(shooter);
	vexTaskRegister(SHOOT_TASK_NAME);
	while(1) {
		//runs the shooter task
		runShootTask(&shooter);

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
void setShootSpeed(int16_t speed) {
	vexMotorSet(SHOOT_MOTOR_1, speed);
    vexMotorSet(SHOOT_MOTOR_2, -speed);
}

//get the shooter encoder's count
int32_t getShooterEncoderValue(void) {
	return vexEncoderGet(getShooterEncoderID());
}

//gets the ID of the shooter encoder
int16_t getShooterEncoderID(void) {
	return vexMotorEncoderIdGet(SHOOT_MOTOR_1);
}

//rotate towards degrees
void rotateTowardsDegrees(int32_t degrees) {
	//starts the encoder
	vexEncoderStart(getShooterEncoderID());
	while(abs(getShooterEncoderValue()) < abs(degrees)) {
		setShootSpeed(sign(degrees)* DEFAULT_SHOOTER_SPEED);
	}
	//sets the motor speeds back to 0
	setShootSpeed(0);
	//sets the encoder value back to 0
	vexEncoderSet(getShooterEncoderID(), 0);
}
