/**
 * \file manualServos.cpp
 * \brief Manual controls of the six Servos through the Serial Monitor.
**/

#include <Arduino.h>
#include <XL320.h>
#include <AX12A.h>

#include "../include/goal.h"
#include "../include/goalslist.h"


#define BYPASS_TIRETTE

#define DirectionPin  (10u)
#define BaudRate    (1000000ul)
#define ID    (254u)
#define XLR1 1
#define XLR2 3
#define XLL1 2
#define XLL2 4


extern GoalsList goalsList;


/**
 * \brief Parse Serial input and move servos accordingly. Never finish.
**/
class ManualServos : public Goal {
public:
	ManualServos() : Goal() {}

	virtual void process();

private:
	char arm = 'R';
	char servo_nb = '0';
	bool initDone = false;
};

void ManualServos::process() {
	if (!initDone) {
		#ifndef DEBUG
		Serial.begin(115200);
		#endif // NOT DEBUG

		Serial.setTimeout(100); // Serial.parseInt() timeout

		// TODO : Temp init servos here
		initDone = true;
	}

	// Commands should looks like:
	// [R/L][0-2]:[position]
	// Where:
	// - First char is either 'R' or 'L' for selecting Right or Left arm
	// - Second char is a digit between 0 and 2 for selecting servo 0, 1 or 2 (0 is the rack and pinion)
	// - Third is a colon ':' as a separtator
	// - Following chars are digits representing a position
	// Alternative command is position only to work on the same servo as previously:
	// [position]
	char c1, c2;
	if (Serial.available()) {
		c1 = Serial.peek();
		if (c1 == 'R' || c1 == 'L') {
			c1 = Serial.read();
			c2 = Serial.read();
			if (!(c2 == '0' || c2 == '1' || c2 == '2')) {
				// Error : wrong servo number
				Serial.println("Error: Wrong servo number");
				Serial.flush();
				return;
			}
			if (Serial.read() != ':') {
				// Error : ':' should be next to a letter
				Serial.println("Error: ':' should be next to a letter");
				Serial.flush();
				return;
			}
			arm = c1;
			servo_nb = c2;
			return;
		}
		if ((c1 < 48) || (c1 > 57)) { // not a digit
			Serial.read(); // Discard the first char which is invalid
			return;
		}
		int position = Serial.parseInt();

		if (arm == 'R') {
			switch (servo_nb) {
				case '0':
					// TODO : move servo R0 to `position`
					break;
				case '1':
					// TODO : move servo R1 to `position`
					break;
				case '2':
					// TODO : move servo R2 to `position`
					break;
			}
		}
		else {
			switch (servo_nb) {
				case '0':
					// TODO : move servo L0 to `position`
					break;
				case '1':
					// TODO : move servo L1 to `position`
					break;
				case '2':
					// TODO : move servo L2 to `position`
					break;
			}
		}
	}
}


void fillGoals() {
	goalsList.addGoal(new ManualServos());
}
