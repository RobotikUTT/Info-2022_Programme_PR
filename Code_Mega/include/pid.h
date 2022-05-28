/**
 * \file pid.h
 * \brief Basic PID class.
**/

#ifndef PID_H
#define PID_H

#include <Arduino.h>

#include "parameters.h"

#define SLIDING_AVG_NB 50

class PID {
public:
	PID(float P, float I, float D, float maxIError) : P(P), I(I), D(D), maxIError(maxIError) {}

	/**
	 * \brief updates the errors and computes the result.
	 * \return PID output
	**/
	float output(float newError);
	void resetErrors();

	float getP() { return P; }
	float getI() { return I; }
	float getD() { return D; }

	float getError() { return error; }
	float getErrorSum() { return errorSum; }
	float getDerivativeError() { return derivativeError; }

private:
	float P, I, D;
	float maxIError;
	float error = 0;
	float errorSum = 0;
	float derivativeError = 0;
	float lastError = 0;
	unsigned long lastErrorTime = 0;

	float slidingAvgTab[SLIDING_AVG_NB] = {0};
	float slidingAvgSum = 0;
	uint8_t slidingAvgIdx = 0;
	// uint8_t nbVal = 0;

	void updateErrors(float error);
};

#endif // PID_H
