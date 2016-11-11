/* Autonomous mode */
#include "../ports.h"
#include "../systems.h"
#include "vex.h"
#include "ch.h"
#include <stdlib.h>

#define DEFAULTSHOOTSPEED 67
#define DEFAULTDRIVESPEED 67
//the task to run
void driveAndShootAuton(void) {
	//drive forward for 3s
	motorDriveControlRight(DEFAULTDRIVESPEED);
	motorDriveControlLeft(DEFAULTDRIVESPEED);
	vexSleep(3000);

	//lift the shooter up for 1.5s
	setShootSpeeds(DEFAULTSHOOTSPEED);
	vexSleep(1500);

	//turn right for 1.5s
	motorDriveControlRight(-DEFAULTDRIVESPEED );
	motorDriveControlLeft(DEFAULTDRIVESPEED);
	vexSleep(1500);

	//drive forward for 5s
	motorDriveControlRight(DEFAULTDRIVESPEED);
	motorDriveControlLeft(DEFAULTDRIVESPEED);
	vexSleep(5000);

	//lift the shooter up for 5s
	setShootSpeeds(DEFAULTSHOOTSPEED);
	vexSleep(5000);
}
