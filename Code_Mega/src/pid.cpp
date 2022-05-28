/**
 * \file pid.cpp
 * \brief Basic PID class.
**/

#include "../include/pid.h"


float PID::output(float newError) {
	updateErrors(newError);
	return P * error + I * errorSum + D * derivativeError;
}

void PID::updateErrors(float newError) {
	error = newError;
	errorSum += error;
	if (errorSum > maxIError) {
		errorSum = maxIError;
		// errorSum = 0;
	} else if (errorSum < - maxIError) {
		errorSum = - maxIError;
	}
	// derivativeError = (error - lastError) * 1000.0 / TIMER_MS;
	// unsigned long deltaT = TIMER_MS;
	// if (lastErrorTime) { 
	// 	deltaT = millis() - lastErrorTime;
	// }
	// derivativeError = (error - lastError) * 1000.0 / deltaT;
	derivativeError = (error - lastError);
	// if (nbVal >= SLIDING_AVG_NB) {
	// 	slidingAvgSum -= slidingAvgTab[slidingAvgIdx];
	// } else {
	// 	nbVal++;
	// }
	// slidingAvgSum -= slidingAvgTab[slidingAvgIdx];
	// slidingAvgTab[slidingAvgIdx] = derivativeError;
	// slidingAvgSum += derivativeError;
	// slidingAvgIdx = (slidingAvgIdx + 1) % SLIDING_AVG_NB;

	// derivativeError = slidingAvgSum / SLIDING_AVG_NB;

	lastError = error;
	// lastErrorTime = millis();

	#ifdef DEBUG_PID
	Serial.print("PID ERROR: ");
	Serial.println(error);
	Serial.print("PID SUM ERROR: ");
	Serial.println(errorSum);
	Serial.print("PID DERIVATIVE ERROR: ");
	Serial.println(derivativeError);
	#endif // DEBUG_PID
}

void PID::resetErrors() {
	error = 0;
	errorSum = 0;
	derivativeError = 0;
	lastError = 0;
	lastErrorTime = 0;

	slidingAvgSum = 0;
	slidingAvgIdx = 0;
	for(uint8_t i=0; i<SLIDING_AVG_NB; i++) {
		slidingAvgTab[i] = 0;
	}
}
