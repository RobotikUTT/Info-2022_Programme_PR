/**
 * \file motor.h
 * \brief Class which represents and commands a motor.
**/

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#include "pins.h" 
#include "parameters.h" 

class Motor {
public:
	Motor(uint8_t forwardPin, uint8_t backwardPin, uint8_t pwmPin, char dbg_id);

	void init(bool enableAfterInit);
	void enable(bool isEnable);
	void sendPWM(uint8_t pwm, bool dirForward, bool force=false);

	uint8_t getCurrentPWM() { return currentPWM; }
	bool getCurrentDir() { return currentDir; }

private:
	uint8_t forwardPin;
	uint8_t backwardPin;
	uint8_t pwmPin;
	char dbg_id;

	uint8_t currentPWM = 0;
	bool currentDir = true;   // True = Forward
	bool isEnabled = false;
};

#endif // MOTOR_H
