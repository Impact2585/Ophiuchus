/*
 * liftsystem.c
 */

#include "../systems.h"
#include "../ports.h"
#include "vex.h"
#include "ch.h"

static char* TASK_NAME = "lift";

// the task to run
void runLiftTask(void) {
	int16_t isTopPressed = vexControllerGet(LIFT_FOWARD);
	int16_t isBotPressed = vexControllerGet(LIFT_BACK);

	if (isTopPressed) {
		setLiftSpeed(DEFAULT_LIFT_SPEED);
	}

	else if (isBotPressed) {
		setLiftSpeed(-DEFAULT_LIFT_SPEED);
	}

	else {
		setLiftSpeed(0);
	}
}

static WORKING_AREA(waLifterTask, DEFAULT_WA_SIZE);

// the lift thread task
static msg_t liftTask(void* arg) {
	(void) arg;
	vexTaskRegister(TASK_NAME);
	while (1) {
		runLiftTask();
		vexSleep(25);
	}

	return (msg_t) 0;

}

// the thread to run the lift task
void initializeLiftSystemThread(void) {
	chThdCreateStatic(waLifterTask, sizeof(waLifterTask), NORMALPRIO - 1,
			liftTask, NULL );
}

// Sets lift speed
void setLiftSpeed(int16_t speed) {
	vexMotorSet(LIFT_MOTOR_1, speed);
	vexMotorSet(LIFT_MOTOR_2, -speed);
}
