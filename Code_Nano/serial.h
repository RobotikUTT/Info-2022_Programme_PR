//
// Created by thgir on 26/05/2022.
//

#ifndef GROS_ROBOT_SERIAL_H
#define GROS_ROBOT_SERIAL_H

#include <Arduino.h>

void init_software_serial();

/**
 * Write in the software serial to communicate to the Mega the distance between a captor and the nearest.
 * The values of distances must be sent in the same order as the numbering of the sonars.
 * Elsewhere the program is irremediably messed.
 * @param message the distance to send, in millimeters. Encoded on 8 bits, so if the detected distance is >255mm,
 * floor it to 255 before calling the function.
 */
void serial_out(uint8_t message);


/**
 * Receive the last byte sent by the Mega and use its value to display the current score on the LCD.
 */
void serial_in();

#endif //GROS_ROBOT_SERIAL_H
