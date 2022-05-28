/**
 * \file collisions.cpp
 * \brief Class which holds a maximal speed value based on the proximity of obstacles.
**/


// #include "robotstate.h"
//#include "goal.h"

#include "../include/collisions.h"

Collisions collisions;
extern RobotState robotState;
extern Nano nano;

void Collisions::update() {
	uint8_t activeSonars = nano.getSonarState() & ~nano.getSonarInhib();
	WheelSpeeds currSpeed = robotState.getWheelSpeeds();

	if (activeSonars & SONAR_FRONT_RIGHT) {
		if (currSpeed.right > 0 && activeCounts[0] < TRESHOLD_COUNT) {
			activeCounts[0]++;
		}
	}
	else {
		if (activeCounts[0]) activeCounts[0]--;
	}

	if (activeSonars & SONAR_FRONT_LEFT) {
		if (currSpeed.right < 0 && activeCounts[1] < TRESHOLD_COUNT) {
			activeCounts[1]++;
		}
	}
	else {
		if (activeCounts[1]) activeCounts[1]--;
	}

	if (activeSonars & SONAR_BACK_RIGHT) {
		if (currSpeed.left > 0 && activeCounts[2] < TRESHOLD_COUNT) {
			activeCounts[2]++;
		}
	}
	else {
		if (activeCounts[2]) activeCounts[2]--;
	}

	if (activeSonars & SONAR_BACK_LEFT) {
		if (currSpeed.left > 0 && activeCounts[3] < TRESHOLD_COUNT) {
			activeCounts[3]++;
		}
	}
	else {
		if (activeCounts[3]) activeCounts[3]--;
	}

	// Hysteresis on activeCounts
	if (maxSpeed) {
		if (
			activeCounts[0] >= TRESHOLD_COUNT ||
			activeCounts[1] >= TRESHOLD_COUNT ||
			activeCounts[2] >= TRESHOLD_COUNT ||
			activeCounts[3] >= TRESHOLD_COUNT
		) {
			maxSpeed = 0;
			#ifdef DEBUG_SONAR
			Serial.print("STOP ! ");
			if (activeCounts[0] >= TRESHOLD_COUNT) {
				Serial.print("SONAR_FRONT_RIGHT ");
			}
			if (activeCounts[1] >= TRESHOLD_COUNT) {
				Serial.print("SONAR_FRONT_LEFT ");
			}
			if (activeCounts[2] >= TRESHOLD_COUNT) {
				Serial.print("SONAR_BACK_RIGHT ");
			}
			if (activeCounts[3] >= TRESHOLD_COUNT) {
				Serial.print("SONAR_BACK_LEFT ");
			}
			Serial.write('\n');
			#endif // DEBUG_SONAR
		}
	}
	else {
		if(!(
			activeCounts[0] ||
			activeCounts[1] ||
			activeCounts[2] ||
			activeCounts[3]
		)) {
			maxSpeed = MAX_SPEED;
			#ifdef DEBUG_SONAR
			Serial.println("GO ! ");
			#endif // DEBUG_SONAR
		}
	}
}
