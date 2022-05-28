/**
 * \file robotstate.h
 * \brief Class which holds position and speed data and updates with coders.
**/

#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#define ENCODER_USE_INTERRUPTS

#include <Encoder.h>

#include "pins.h"
#include "parameters.h"


typedef struct {float x, y, theta;} Position;
typedef struct {float left, right;} WheelSpeeds;


class RobotState  {
public:
    /**
    * \brief Updates wheel speeds and position from coders.
    **/
    void update();

    void setPosition(Position pos) { position = pos; }
    Position getPosition() const { return position; }
    WheelSpeeds getWheelSpeeds() const { return wheelSpeeds; }

private:
    Position position = {0, 0, 0}; // mm, mm, rad
    WheelSpeeds wheelSpeeds = {0, 0}; // mm/s, mm/s

};

#endif // ROBOTSTATE_H
