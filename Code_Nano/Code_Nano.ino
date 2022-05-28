#include <Arduino.h>

#include "sensors.h"
#include "pins.h"
#include "displayer.h"
#include "serial.h"



void setup() {
    init_software_serial();
    Serial.begin(9600);
    init_sonars();
    init_lcd();
    display_score(0);
}


void loop() {
    static uint8_t message = 0x00;

    serial_in();

    for (int i = 0; i < NB_CAPTORS; ++i) {
        double distance = get_distance(i);
        if (distance < 200 && distance)
            message |= 0b1 << i;  // set the i-th bit to 1
        else
            message &= ~(0b1 << i);  // set the i-th bit to 0
        serial_out(message);
    }
}


