//
// Created by thgir on 25/05/2022.
//

#ifndef GROS_ROBOT_PINS_H
#define GROS_ROBOT_PINS_H

#include <Arduino.h>

#define NB_CAPTORS 4
#define SW_RX A0
#define SW_TX A1

const static uint8_t trigger_pins[NB_CAPTORS] {4, 6, 8, 10};
const static uint8_t echo_pins[NB_CAPTORS] {5, 7, 9, 11};

#endif //GROS_ROBOT_PINS_H
