/**
 * \file control.cpp
 * \brief Class which sends PWM values to motors to regulate them at given speeds.
**/

#include "../include/control.h"

extern RobotState robotState;
extern Collisions collisions;
extern Motor leftMotor;
extern Motor rightMotor;

Control control;


void Control::resetPIDs() {
	linearPID.resetErrors();
	angularPID.resetErrors();
	leftWheelPID.resetErrors();
	rightWheelPID.resetErrors();
}

void Control::updateSpeeds(float distanceError, float thetaError, float maxLinearSpeed) {
	// static float lastDistanceError = 0;
	// distanceError = (distanceError + lastDistanceError) / 2;
	// lastDistanceError = distanceError;
	float targetLinearSpeed = filterLinearSpeed(linearPID.output(distanceError), maxLinearSpeed);
	float targetAngularSpeed = filterAngularSpeed(angularPID.output(thetaError));
	updateMotorsSpeeds(targetLinearSpeed, targetAngularSpeed);
}

void Control::updateMotorsSpeeds(float targetLinearSpeed, float targetAngularSpeed) {
	// static float lastLeftError = 0, lastRightError = 0;

	targetLeftSpeed = targetLinearSpeed - targetAngularSpeed;
	targetRightSpeed = targetLinearSpeed + targetAngularSpeed;
	float leftError = 0;
	float rightError = 0;

	// if (abs(robotState.getWheelSpeeds().left) > abs(targetLeftSpeed)){
	// 	leftError = 0;
	// }
	// else {
	// 	leftError = targetLeftSpeed - robotState.getWheelSpeeds().left;
	// }
	// if (abs(robotState.getWheelSpeeds().right) > abs(targetRightSpeed)){
	// 	rightError = 0;
	// }
	// else {
	// 	rightError = targetRightSpeed - robotState.getWheelSpeeds().right;
	// }
	leftError = targetLeftSpeed - robotState.getWheelSpeeds().left;
	rightError = targetRightSpeed - robotState.getWheelSpeeds().right;

	// leftError = (leftError + lastLeftError) / 2;
	// lastLeftError = leftError;

	// rightError = (rightError + lastRightError) / 2;
	// lastRightError = rightError;

	updateMotor(leftMotor, leftWheelPID, leftError, targetLeftSpeed);
	updateMotor(rightMotor, rightWheelPID, rightError, targetRightSpeed);
}

void Control::updateMotor(Motor &motor, PID &pid, float error, float targetSpeed) {
	int pwm = pid.output(error);
	bool dirForward;
	if (!targetSpeed) {
		dirForward = motor.getCurrentDir();
		pwm = 0;
	}
	else if (targetSpeed >= 0) {
		dirForward = true;
		pwm = max(pwm, 0);
	}
	else {
		dirForward = false;
		pwm = -min(pwm, 0);
	}

	if (pwm > 255) pwm = 255;

	motor.sendPWM(pwm, dirForward);
}

float Control::filterLinearSpeed(float speed, float maxSpeed) {
	if (!maxSpeed) {
		maxSpeed = MAX_SPEED;
	}

	if (speed >= 0) {
		if (speed > collisions.getMaxSpeed()) {
			speed = collisions.getMaxSpeed();
		}

		if (speed - currentLinearSpeed > MAX_ACCELERATION_DIFFERENCE) {
			speed = currentLinearSpeed + MAX_ACCELERATION_DIFFERENCE;
		} else if (speed - currentLinearSpeed < - MAX_BRAKE_DIFFERENCE) {
			speed = currentLinearSpeed - MAX_BRAKE_DIFFERENCE;
		}

		if (speed > maxSpeed) {
			speed = maxSpeed;
		}
	}
	else { // speed < 0 : going backwards
		if (speed < - collisions.getMaxSpeed()) {
			speed = - collisions.getMaxSpeed();
		}

		if (speed - currentLinearSpeed < - MAX_ACCELERATION_DIFFERENCE) {
			speed = currentLinearSpeed - MAX_ACCELERATION_DIFFERENCE;
		} else if (speed - currentLinearSpeed > MAX_BRAKE_DIFFERENCE) {
			speed = currentLinearSpeed + MAX_BRAKE_DIFFERENCE;
		}

		if (speed < - maxSpeed) {
			speed = - maxSpeed;
		}
	}

	currentLinearSpeed = speed;
	return speed;
}

float Control::filterAngularSpeed(float speed) {
	if (speed >= 0) {
		if (speed > collisions.getMaxSpeed()) {
			speed = collisions.getMaxSpeed();
		}

		if (speed - currentAngularSpeed > MAX_ANGULAR_ACCELERATION_DIFFERENCE) {
			speed = currentAngularSpeed + MAX_ANGULAR_ACCELERATION_DIFFERENCE;
		} else if (speed - currentAngularSpeed < - MAX_ANGULAR_BRAKE_DIFFERENCE) {
			speed = currentAngularSpeed - MAX_ANGULAR_BRAKE_DIFFERENCE;
		}

		if (speed > MAX_ANGULAR_SPEED) {
			speed = MAX_ANGULAR_SPEED;
		}
	}
	else { // speed < 0 : going backwards
		if (speed < - collisions.getMaxSpeed()) {
			speed = - collisions.getMaxSpeed();
		}

		if (speed - currentAngularSpeed < - MAX_ANGULAR_ACCELERATION_DIFFERENCE) {
			speed = currentAngularSpeed - MAX_ANGULAR_ACCELERATION_DIFFERENCE;
		} else if (speed - currentAngularSpeed > MAX_ANGULAR_BRAKE_DIFFERENCE) {
			speed = currentAngularSpeed + MAX_ANGULAR_BRAKE_DIFFERENCE;
		}

		if (speed < - MAX_ANGULAR_SPEED) {
			speed = - MAX_ANGULAR_SPEED;
		}
	}

	currentAngularSpeed = speed;
	return speed;
}
