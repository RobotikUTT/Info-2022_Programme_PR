/**
 * \file contrnanool.cpp
 * \brief Class handle communication and interface with the Arduino Nano program.
**/


#include "../include/nano.h"

Nano nano;


Nano::Nano() {
    SERIAL_NANO.begin(9600);
}

void Nano::updateSonar() {
    while (SERIAL_NANO.available()) {
        sonarState = SERIAL_NANO.read();
    }
}

void Nano::sendScore(uint8_t score) {
    SERIAL_NANO.write(score);
}
