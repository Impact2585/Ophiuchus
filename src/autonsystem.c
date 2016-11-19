/* Autonomous mode */
#include "../ports.h"
#include "../systems.h"
#include "vex.h"
#include "ch.h"
#include <stdlib.h>

//auton task that drives forward, picks up a ball, and shoots a low goal
void driveAndShootAuton(void) {
	//drive forward for 3s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(3000);

	//lift the shooter up for 1.5s
	setShootSpeeds(DEFAULT_SHOOTER_SPEED);
	vexSleep(1500);

	//turn right for 1.5s
	motorDriveControlRight(-AUTON_DRIVE_SPEED );
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(1500);

	//drive forward for 5s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(5000);

	//lift the shooter up for 5s
	setShootSpeeds(DEFAULT_SHOOTER_SPEED);
	vexSleep(5000);
}
