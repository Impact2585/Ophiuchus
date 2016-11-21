/* Autonomous mode */
#include "../ports.h"
#include "../systems.h"
#include "vex.h"
#include "ch.h"
#include <stdlib.h>

//auton task that drives forward, picks up an object, and shoots a low goal
void driveAndShootAuton(void) {
	//drive forward for 3s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(3000);

	//lift down the shooter and lock it
	primeForShooting();

	//drive forward for 0.5s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(500);

	//turn left for 1.5s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(-AUTON_DRIVE_SPEED);
	vexSleep(1500);

	//drive forward for 5s
	motorDriveControlRight(AUTON_DRIVE_SPEED);
	motorDriveControlLeft(AUTON_DRIVE_SPEED);
	vexSleep(5000);

	//release the shooter
	releaseLock();
}
