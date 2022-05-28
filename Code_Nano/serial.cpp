//
// Created by thgir on 26/05/2022.
//

#include "serial.h"
#include "pins.h"
#include "displayer.h"
#include <SoftwareSerial.h>

#define MSG_PERIOD 5  /* 20 Hz => 5 milliseconds */

SoftwareSerial serial(SW_RX, SW_TX);

void init_software_serial() {
    serial.begin(9600);
    serial.listen();
}

void serial_out(const uint8_t message) {
    static unsigned long elapsed = 0;
    const unsigned long current = millis();
    if (current - elapsed >= MSG_PERIOD) {
        elapsed = current;
        serial.write(message);
    }
}


void serial_in() {
    static int msg_in = 0;
    if (serial.available() > 0) {
        const int new_message = serial.read();
        if (new_message != msg_in) {
            msg_in = new_message;
            display_score(msg_in);
        }
    }
}
