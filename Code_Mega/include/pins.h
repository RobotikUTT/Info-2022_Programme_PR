/**
 * \file pins.h
 * \brief Pin map definition.
**/

#include <Arduino.h>

#ifndef PINS_H
#define PINS_H

/* Coders */
#define ENCODER_RIGHT_A		2
#define ENCODER_RIGHT_B		3

#define ENCODER_LEFT_A		20
#define ENCODER_LEFT_B		21

/* Motors */
#define MOT_RIGHT_FORWARD	11
#define MOT_RIGHT_BACKWARD	13
#define MOT_RIGHT_PWM		12

#define MOT_LEFT_FORWARD	9
#define MOT_LEFT_BACKWARD	8
#define MOT_LEFT_PWM		10

/* Actuators */
#define VACUUM_PUMP_RIGHT	6
#define VACUUM_PUMP_LEFT	7

#define SERIAL_AX12A	Serial1
#define SERIAL_XL320	Serial2
#define SERIAL_NANO		Serial3

/* Status Leds */
#define LED_RED				A0
#define LED_GREEN			A1
#define LED_BLUE			A2
#define LED_SIDE_YELLOW     52
#define LED_SIDE_PURPLE     53

/* Sensors */
#define CURRENT_VPUMP_RIGHT	A3
#define CURRENT_VPUMP_LEFT	A4

#define TIRETTE				4
#define SWITCH_SIDE_SELECT	5


#endif // PINS_H
