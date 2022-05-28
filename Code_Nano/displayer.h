//
// Created by thgir on 25/05/2022.
//

#ifndef GROS_ROBOT_DISPLAYER_H
#define GROS_ROBOT_DISPLAYER_H

//#include "lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include <LiquidCrystal_I2C.h>

void init_lcd();
void display_score(uint8_t score);

#endif //GROS_ROBOT_DISPLAYER_H
