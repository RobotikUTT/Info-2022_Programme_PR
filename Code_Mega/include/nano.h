/**
 * \file contrnanool.h
 * \brief Class handle communication and interface with the Arduino Nano program.
**/

#ifndef NANO_H
#define NANO_H

#include <Arduino.h>

#include "pins.h"

class Nano {
public:
    Nano();

    void updateSonar();
    void sendScore(uint8_t score);

    uint8_t getSonarState() { return sonarState; }
    uint8_t getSonarInhib() { return sonarInhib; }
    void setSonarInhib(uint8_t value) { sonarInhib = value; }

private:
    // x bits are mapped to x sonars
    uint8_t sonarState = 0; // bit set to 1 means sonar is active
    uint8_t sonarInhib = 0; // bit set to 1 means sonar state is ignored

};

#endif // NANO_H
