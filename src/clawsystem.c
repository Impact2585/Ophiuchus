/*
 * clawsystem.c
 */

#include "../ports.h"
#include "../systems.h"

static char* TASK_NAME = "claw";

//runs the claw system
void runClawSystem(void) {
	if(vexControllerGet(OPEN_CLAW))
		setClawSpeed(1);
	else if(vexControllerGet(CLOSE_CLAW))
		setClawSpeed(-1);
	else {

	if(vexControllerGet(OPEN_CLAW_LEFT))
		vexMotorSet(CLAW_MOTOR_LEFT, CLAW_SPEED);
	else if(vexControllerGet(CLOSE_CLAW_LEFT))
		vexMotorSet(CLAW_MOTOR_LEFT, -CLAW_SPEED);
	else if(vexControllerGet(OPEN_CLAW_RIGHT))
		vexMotorSet(CLAW_MOTOR_RIGHT, -CLAW_SPEED);
	else if(vexControllerGet(CLOSE_CLAW_RIGHT))
		vexMotorSet(CLAW_MOTOR_RIGHT, CLAW_SPEED);
	else
		setClawSpeed(0);
	}
}

static WORKING_AREA(waClawTask, DEFAULT_WA_SIZE);

//the claw system thread
static msg_t clawSystemThread(void* arg) {
	(void)arg;
	vexTaskRegister(TASK_NAME);
	while(1) {
		runClawSystem();
		vexSleep(25);
	}
	return (msg_t)0;
}

//creates the thread for the claw system
void initializeClawSystemThread(void) {
	chThdCreateStatic(waClawTask, sizeof(waClawTask), NORMALPRIO - 1, clawSystemThread, NULL);
}

//move the claw for a certain time 
void moveClaw(int16_t open) {
	setClawSpeed(open);
	vexSleep(500);
	setClawSpeed(0);
}

//opens the claw if 1 closes the claw if -1
void setClawSpeed(int16_t open) {
	vexMotorSet(CLAW_MOTOR_LEFT, open * CLAW_SPEED);
	vexMotorSet(CLAW_MOTOR_RIGHT, open * -CLAW_SPEED);
}
