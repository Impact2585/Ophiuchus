/*
 * liftsystem.c
 */
#include "../systems.h"
#include "../ports.h"

static char* LIFT_TASK_NAME = "lift";

//the lift task to run
void runLiftTask(void) {
	int16_t shouldShoot = vexControllerGet(SHOOT);

	//moves forward then back
	if(shouldShoot) {
		setLiftSpeeds(DEFAULT_LIFT_SPEED);
		vexSleep(300);
		setLiftSpeeds(-DEFAULT_LIFT_SPEED);
		vexSleep(300);
		setLiftSpeeds(0);
	}
}

//default working area of the thread 512
static WORKING_AREA(waLiftTask, DEFAULT_WA_SIZE);

//the lift task thread
static msg_t liftTask(void* arg) {
	(void)arg;
	vexTaskRegister(LIFT_TASK_NAME);
	while(1) {
		runLiftTask();
		vexSleep(25);
	}
	return (msg_t)0;
}

//creates a thread that runs the lift task
void initializeLiftSystemThread(void) {
	chThdCreateStatic(waLiftTask, sizeof(waLiftTask), NORMALPRIO - 1, liftTask, NULL);
}

//sets the lift speeds
void setLiftSpeeds(int16_t speed) {
	vexMotorSet(LIFT_MOTOR_1, -speed);
	vexMotorSet(LIFT_MOTOR_2, speed);
}
