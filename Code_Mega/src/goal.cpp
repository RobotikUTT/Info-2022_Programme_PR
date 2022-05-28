/**
 * \file goal.cpp
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#include "../include/goal.h"

#include <math.h>

extern RobotState robotState;
extern Control control;
extern Nano nano;

extern void theEnd();

float diffAngleClosest(float theta_A, float theta_B) {
	// diff between angle with [-pi, pi] boundaries
	float delta = theta_A - theta_B;
	if (delta > M_PI) {
		delta -= 2 * M_PI;
	}
	else if (delta < -M_PI) {
		delta += 2 * M_PI;
	}
	return delta;
}

void Goto::process() {
	if (doSubGoal) {
		if (subGoal->isReached()) {
			control.resetPIDs();
			doSubGoal = false;
		}
		else {
			subGoal->process();
		}
		return;
	}
	if (!stop) {
		float dx = x - robotState.getPosition().x;
		float dy = y - robotState.getPosition().y;
		float targetAngle = atan2(dy, dx);
		if (direction == AUTO) { // Called only in the first process() call
			if (abs(diffAngleClosest(targetAngle, robotState.getPosition().theta)) > M_PI / 2) {
				direction = BACKWARD;
			}
			else {
				direction = FORWARD;
			}
		}
		if (direction == BACKWARD) {
			if (targetAngle < 0) {
				targetAngle += M_PI;
			}
			else {
				targetAngle += M_PI;
			}
		}
		/*Serial.print("dx: ");
		Serial.println(dx );
		Serial.print("dy: ");
		Serial.println(dy);*/

		float distanceError = sqrt(pow(dx, 2) + pow(dy, 2));
		if (direction == BACKWARD) {
			distanceError = - distanceError;
		}
		float thetaError = diffAngleClosest(targetAngle, robotState.getPosition().theta);

		if (!init) {
			init = true;
			normalizedRampStep = RAMP_STEP_GOTO / abs(distanceError) ; // 1 / (abs(distanceError) / RAMP_STEP_GOTO)

			// #ifdef DEBUG_GOAL
			// Serial.print("Theta Error: ");
			// Serial.println(thetaError);
			// Serial.print("targetAngle: ");
			// Serial.println(targetAngle);
			// Serial.print("RobotState.theta: ");
			// Serial.println(robotState.getPosition().theta);
			// #endif // DEBUG_GOAL
			if (thetaError) {
				subGoal = new Rot(targetAngle);
				doSubGoal = true;
				return;
			}
		}

		if (thetaError > M_PI / 2 || thetaError < -M_PI /2) {
			digitalWrite(LED_BLUE, LOW);
			digitalWrite(LED_RED, HIGH);
			theEnd();
		}

		if (abs(distanceError) < DIST_ERROR_TOLERANCE) { //&& abs(thetaError) < THETA_ERROR_TOLERANCE ) {
			stop = true;
			startTimeoutStop = millis();
			// control.resetPIDs();
			control.updateMotorsSpeeds(0, 0);
			#ifdef DEBUG_GOAL
			Serial.println("Goal: Goto Reached");
			#endif // DEBUG_GOAL
		}
		else {
			/*if (thetaError < THETA_ERROR_TOLERANCE  && type==0) {
				// rotate only
				distanceError = 0;
			}*/ 
			//Serial.println("Goto::process()");
			/*Serial.print("thetaError: ");
			Serial.println(thetaError);
			Serial.print("dError: ");
			//Serial.println(distanceError);*/
			rampCoeff = min(1.0, rampCoeff + normalizedRampStep);
			control.updateSpeeds(distanceError * rampCoeff, thetaError * rampCoeff, maxSpeed);
			// control.updateSpeeds(distanceError * rampCoeff, 0, maxSpeed);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
			// Position pos = {x, y, theta};
			// Position pos = {0, 0, 0};
			// robotState.setPosition(pos);
			return;
		}
		control.updateMotorsSpeeds(0, 0);
	}
}

void Rot::process() {
	if (!stop) {
		if (!init) {
			x = robotState.getPosition().x;
			y = robotState.getPosition().y;
		}
		float thetaError = diffAngleClosest(theta, robotState.getPosition().theta);
		if (direction == CLOCKWISE) {
			if (thetaError > 0) {
				thetaError -= 2 * M_PI;
			}
			else { // Direction is ok, switch to CLOSEST to avoid problem in case of overshoot
				direction = CLOSEST;
			}
		}
		else if (direction == COUNTER_CLOCKWISE) {
			if (thetaError < 0) {
				thetaError += 2 * M_PI;
			}
			else { // Direction is ok, switch to CLOSEST to avoid problem in case of overshoot
				direction = CLOSEST;
			}
		}

		if (abs(thetaError) < THETA_ERROR_TOLERANCE) {
			stop = true;
			startTimeoutStop = millis();
			// control.resetPIDs();
			control.updateMotorsSpeeds(0, 0);
		}
		else {
			if (!init) {
				init = true;
				normalizedRampStep = RAMP_STEP_ROT / abs(thetaError); // 1 / (abs(distanceError) / RAMP_STEP_ROT)
			}
			rampCoeff = min(1.0, rampCoeff + normalizedRampStep);
			control.updateSpeeds(0, thetaError * rampCoeff);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
			// Position pos = robotState.getPosition();
			// pos.theta = theta;
			// Position pos = {x, y, theta};
			// robotState.setPosition(pos);
			return;
		}
		control.updateMotorsSpeeds(0, 0);
	}
}


void Jog::process() {
	if (!startTimeGoal) {
		startTimeGoal = millis();
	}
	else if (millis() - startTimeGoal >= duration) {
		if (!startTimeoutStop) {
			startTimeoutStop = millis();
		}
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
			return;
		}
		control.updateMotorsSpeeds(0, 0);
	}
	else {
		float filteredLinearSpeed = control.filterLinearSpeed(linearSpeed, 0);
		float filteredAngularSpeed = control.filterAngularSpeed(angularSpeed);
		control.updateMotorsSpeeds(filteredLinearSpeed, filteredAngularSpeed);
	}
}

void InhibSonar::process() {
	uint8_t sonarInhib_ = nano.getSonarInhib();
	if (inhib) {
		sonarInhib_ |= sonarMask;
	}
	else {
		sonarInhib_ &= ~sonarMask;
	}
	nano.setSonarInhib(sonarInhib_);
	reached = true;
}

void Delay::process() {
	if (!startTime) {
		startTime = millis();
	}
	else if (millis() - startTime >= duration) {
		reached = true;
	}
}
