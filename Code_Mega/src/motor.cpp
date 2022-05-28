/**
 * \file motor.cpp
 * \brief Class which represents and commands a motor.
**/

#include "../include/motor.h"

Motor leftMotor = Motor(MOT_LEFT_FORWARD, MOT_LEFT_BACKWARD, MOT_LEFT_PWM, 'L');
Motor rightMotor = Motor(MOT_RIGHT_FORWARD, MOT_RIGHT_BACKWARD, MOT_RIGHT_PWM, 'R');


Motor::Motor(uint8_t forwardPin, uint8_t backwardPin, uint8_t pwmPin, char dbg_id)
	: forwardPin(forwardPin), backwardPin(backwardPin), pwmPin(pwmPin), dbg_id(dbg_id) {
	// Place init code here if needed
}

void Motor::init(bool enableAfterInit) {
	pinMode(forwardPin, OUTPUT);
	pinMode(backwardPin, OUTPUT);
	pinMode(pwmPin, OUTPUT);
	enable(enableAfterInit);
}

void Motor::enable(bool enabled) {
	if (enabled != isEnabled) {
		isEnabled = enabled;
		if (isEnabled) {
			digitalWrite(forwardPin, currentDir ? HIGH : LOW);
			digitalWrite(backwardPin, currentDir ? LOW : HIGH);
			analogWrite(pwmPin, currentPWM);
		} else {
			digitalWrite(forwardPin, LOW);
			digitalWrite(backwardPin, LOW);
			analogWrite(pwmPin, 0);
		}

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: ");
		Serial.println(isEnabled ? "Enabled" : "Disabled");
		#endif // DEBUG_MOTOR
	}
}

void Motor::sendPWM(uint8_t pwm, bool dirForward, bool force) {
	if (dirForward != currentDir) {
		// Disable motors before changing PWM if changing direction
		digitalWrite(forwardPin, LOW);
		digitalWrite(backwardPin, LOW);
	}

	#ifdef DEBUG_MOTOR
	Serial.write(dbg_id);
	Serial.print(" motor: Curr PWM: ");
	Serial.print(currentPWM);
	Serial.print("; Wanted PWM: ");
	Serial.println(pwm);
	#endif // DEBUG_MOTOR

	if (pwm != currentPWM) {
		if (!force || dirForward == currentDir) {
			if (pwm > currentPWM) {
				if (pwm - currentPWM > MAX_PWM_DIFFERENCE_ACC) {
					if (currentPWM >= 255 - MAX_PWM_DIFFERENCE_ACC) {
						pwm = 255;
					} else {
						pwm = currentPWM + MAX_PWM_DIFFERENCE_ACC;
					}
				}
			}
			else {
				if (currentPWM - pwm > MAX_PWM_DIFFERENCE_BRK) {
					if (currentPWM <= MAX_PWM_DIFFERENCE_BRK) {
						pwm = 0;
					} else {
						pwm = currentPWM - MAX_PWM_DIFFERENCE_BRK;
					}
				}
			}
		}

		if (isEnabled)
			analogWrite(pwmPin, pwm);
		currentPWM = pwm;

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: New PWM: ");
		Serial.println(currentPWM);
		#endif // DEBUG_MOTOR
	}

	if (dirForward != currentDir) {
		if (isEnabled) {
			digitalWrite(forwardPin, dirForward ? HIGH : LOW);
			digitalWrite(backwardPin, dirForward ? LOW : HIGH);
		}
		currentDir = dirForward;

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: New DIR: ");
		Serial.println(dirForward ? "Forward" : "Backward");
		#endif // DEBUG_MOTOR
	}
}
