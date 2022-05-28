/**
 * \file robotstate.cpp
 * \brief Class which holds position and speed data and updates with coders.
**/

#include "../include/robotstate.h"
#include <math.h>

RobotState robotState;
Encoder rightEnc(ENCODER_RIGHT_A, ENCODER_RIGHT_B);
Encoder leftEnc(ENCODER_LEFT_A, ENCODER_LEFT_B);


void RobotState::update() {
	static unsigned long lastMillis = 0;
	static long leftLastTicks = 0, rightLastTicks = 0;
	static float lastAngle = 0;

	int leftTicks = leftEnc.read();
	int rightTicks = rightEnc.read();

	unsigned long
	t = millis(),
	dt = t - lastMillis;

	float dLeft = (float)(leftTicks - leftLastTicks) * DISTANCE_PER_TICK_L;    // mm
	float dRight = (float)(rightTicks - rightLastTicks) * DISTANCE_PER_TICK_R; // mm
	float speedLeft = (1000 * dLeft) / dt;   // mm/s
	float speedRight = (1000 * dRight) / dt; // mm/s
	if (abs(speedLeft) > 10 * MAX_SPEED || abs(speedRight) > 10 * MAX_SPEED) {
		#ifdef DEBUG_ROBOTSTATE
		Serial.println("RobotState: Warning ! Invalid speed value ! Ignoring.");
		#endif // DEBUG_ROBOTSTATE
		return;
	}
	/* LOW PASS FILTER */
	speedLeft = wheelSpeeds.left + ALPHA * (speedLeft - wheelSpeeds.left);
	speedRight = wheelSpeeds.right + ALPHA * (speedRight - wheelSpeeds.right);

	wheelSpeeds.left = speedLeft;
	wheelSpeeds.right = speedRight;

	float dAngle = atan2((dRight - dLeft), ENTRAXE);
	position.theta += dAngle;
	position.theta = fmod(position.theta, 2 * M_PI);
	if (position.theta > M_PI) {
		position.theta -= 2 * M_PI;
	}
	else if (position.theta < -M_PI) {
		position.theta += 2 * M_PI;
	}

	float dDistance = (dRight + dLeft) / 2.0;

	float meanTrajAngle = (position.theta + lastAngle) / 2.0;
	// float meanTrajAngle = (tetaMod + lastAngle) / 2.0;

	position.x += dDistance * cos(meanTrajAngle);
	position.y += dDistance * sin(meanTrajAngle);

	#ifdef DEBUG_ROBOTSTATE
	Serial.print("LeftEnc : ");
	Serial.println(leftTicks);
	Serial.print("RightEnc : ");
	Serial.println(rightTicks);
	Serial.print("WheelSpeeds: Left=");
	Serial.print(wheelSpeeds.left);
	Serial.print("; Right=");
	Serial.println(wheelSpeeds.right);
	Serial.print("Position: X=");
	Serial.print(position.x);
	Serial.print("; Y=");
	Serial.print(position.y);
	Serial.print("; theta=");
	Serial.println(position.theta, 3);  // X.XXX
	#endif // DEBUG_ROBOTSTATE

	lastMillis = t;
	// lastAngle = tetaMod;
	lastAngle = position.theta;
	rightLastTicks = rightTicks;
	leftLastTicks = leftTicks;
}
