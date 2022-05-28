/*
 * \file Code_Mega.ino
 * \brief Holds the Arduino setup and loop functions, which make the robot run.
*/
 
#include <SimpleTimer.h>

#include "include/pins.h"
#include "include/parameters.h"
#include "include/nano.h"
#include "include/motor.h"
#include "include/control.h"
#include "include/collisions.h"
#include "include/robotstate.h"
#include "include/goal.h"
#include "include/goalslist.h"

/************************/
/* ACTION SET SELECTION */
/************************/
// #include "actionsets/manualServos.h"
#include "actionsets/calibration.h"
// #include "actionsets/homologation.h"
// void fillGoals() {};	// Uncomment for no Action Set
/************************/

extern Nano nano;
extern Motor leftMotor;
extern Motor rightMotor;
extern Control control;
extern RobotState robotState;
extern Collisions collisions;
extern GoalsList goalsList;


SimpleTimer asserv_timer = SimpleTimer();
uint32_t matchStart;
bool isSideYellow;

void waitForTirette();
void asservLoop();
void theEnd();

void setup() {
	#ifdef DEBUG
	Serial.begin(115200);
	Serial.println(">>> Robot Startup - Robotik 2022 <<");
	#endif // DEBUG
	#ifdef PLOT
	Serial.begin(115200);
	Serial.write('\n');
	Serial.flush();

	#ifdef PLOT_MOTOR_SPD
	Serial.print("L_SPEED");
	Serial.print(":0.0");
	Serial.write(',');
	Serial.print("L_PWM");
	Serial.print(":0.0");
	Serial.write(',');
	#endif // PLOT_MOTOR_SPD
	#ifdef PLOT_MOTOR_ERR
	Serial.print("L_ERR_P");
	Serial.print(":0.0");
	Serial.write(',');
	Serial.print("L_ERR_I");
	Serial.print(":0.0");
	Serial.write(',');
	Serial.print("L_ERR_D");
	Serial.print(":0.0");
	Serial.write(',');
	#endif // PLOT_MOTOR_ERR
	#ifdef PLOT_MOTOR_TGT
	Serial.print("L_TARGET");
	Serial.print(":0.0");
	#endif // PLOT_MOTOR_TGT
	Serial.write('\n');
	#endif // PLOT

	asserv_timer.setInterval(TIMER_MS, asservLoop);

	pinMode(TIRETTE, INPUT_PULLUP);
	pinMode(SWITCH_SIDE_SELECT, INPUT_PULLUP);
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);
	pinMode(LED_SIDE_YELLOW, OUTPUT);
	pinMode(LED_SIDE_PURPLE, OUTPUT);

	leftMotor.init(true);
	rightMotor.init(true);

	checkSwitchSideSelect(true);
	#ifndef BYPASS_TIRETTE
	waitForTirette();
	#endif // NOT BYPASS_TIRETTE
	checkSwitchSideSelect(false);
	Position reset_pos = {0, 0, 0};
	robotState.setPosition(reset_pos);

	matchStart = millis();
	fillGoals();
}

void loop() {
	asserv_timer.run();
	if (millis() - matchStart > MATCH_LENGTH_MS) {
		theEnd();
	}
}

void theEnd() {
	leftMotor.enable(false);
	rightMotor.enable(false);
	// TODO : vacuum pumps OFF
	// What about servos ?
	digitalWrite(LED_BLUE, LOW);
	digitalWrite(LED_GREEN, HIGH);
	while (true);
}

void asservLoop() {
	nano.updateSonar();
	robotState.update();
	collisions.update();
	goalsList.processCurrentGoal();
	#ifdef PLOT
	plot();
	#endif // PLOT
	delay(1);
}

void waitForTirette() {
	uint32_t last_millis = 0;
	bool led_state = false;

	// Wait for Tirette insertion
	if (digitalRead(TIRETTE)) {
		#ifdef DEBUG_MATCH
		Serial.println("/!\\ Tirette not in place ! Waiting..");
		#endif // DEBUG_MATCH
		while (digitalRead(TIRETTE)) {
			if (millis() - last_millis > 150) {
				last_millis = millis();
				digitalWrite(LED_RED, led_state ^= 1);
			}
			checkSwitchSideSelect(false);
			delay(1);
		}
		digitalWrite(LED_RED, led_state = false);
		delay(300);
	}

	// Wait for Tirette withdrawal
	#ifdef DEBUG_MATCH
	Serial.println("Waiting Tirette signal to start the match !");
	#endif // DEBUG_MATCH
	while (!digitalRead(TIRETTE)) {
		if (millis() - last_millis > 350) {
			last_millis = millis();
			digitalWrite(LED_BLUE, led_state ^= 1);
		}
		checkSwitchSideSelect(false);
		delay(1);
	}
	digitalWrite(LED_BLUE, HIGH);
	#ifdef DEBUG_MATCH
	Serial.println("Gooo !");
	#endif // DEBUG_MATCH
}

void checkSwitchSideSelect(bool force) {
	if (force || isSideYellow != !digitalRead(SWITCH_SIDE_SELECT)) {
		isSideYellow = !digitalRead(SWITCH_SIDE_SELECT);
		if (isSideYellow) {
			digitalWrite(LED_SIDE_YELLOW, HIGH);
			digitalWrite(LED_SIDE_PURPLE, LOW);
		}
		else {
			digitalWrite(LED_SIDE_YELLOW, LOW);
			digitalWrite(LED_SIDE_PURPLE, HIGH);
		}
		#ifdef DEBUG_MATCH
		Serial.print("Side Selected: ");
		Serial.println(isSideYellow ? "YELLOW" : "PURPLE");
		#endif // DEBUG_MATCH
	}
}

void plot() {
	static int cpt = 0;
	if (!cpt) {
		#ifdef PLOT_MOTOR_SPD
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		Serial.print(currSpeed.left);
		Serial.write(' ');
		Serial.print((leftMotor.getCurrentDir() ? 1 : -1) * leftMotor.getCurrentPWM());
		Serial.write(' ');
		// Serial.print(currSpeed.right);
		// Serial.write(' ');
		#endif // PLOT_MOTOR_SPD
		#ifdef PLOT_MOTOR_ERR
		PID pidL = control.getLeftWheelPID();
		// PID pidL = control.getAngularPID();
		// PID pidL = control.getLinearPID();
		// PID pidR = control.getRightWheelPID();
		Serial.print(pidL.getError() * pidL.getP());
		Serial.write(' ');
		Serial.print(pidL.getErrorSum() * pidL.getI());
		Serial.write(' ');
		Serial.print(pidL.getDerivativeError() * (pidL.getD() ? pidL.getD() : 0.01));
		Serial.write(' ');
		#endif // PLOT_MOTOR_ERR
		#ifdef PLOT_MOTOR_TGT
		Serial.print(control.getTargetLeftSpeed());
		#endif // PLOT_MOTOR_TGT
		Serial.write('\n');
	}
	cpt = (cpt + 1) % 1;
}
