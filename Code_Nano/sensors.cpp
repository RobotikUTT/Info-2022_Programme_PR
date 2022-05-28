//
// Created by thgir on 25/05/2022.
//

#include "sensors.h"
#include "pins.h"

/* Constante pour le timeout ; 5ms = ~1.7m à 340m/s */
#define MEASURE_TIMEOUT 5000UL
#define SOUND_SPEED 0.34  /* In mm per microsecond */
#define SOUND_SPEED_MPS 340.5  /* In m per second */
#define SOUND_SPEED_UPS 340.5  /* In m per microsecond */


void init_sonars() {
    for (int i = 0; i < NB_CAPTORS; ++i) {
        pinMode(trigger_pins[i], OUTPUT);
        digitalWrite(trigger_pins[i], LOW);
        pinMode(echo_pins[i], INPUT);
    }
}

/**
 * Retourne la distance qui sépare le capteur du plus proche obstacle
 * @param captor_index
 * @return
 */
double get_distance(const int captor_index) {
    digitalWrite(trigger_pins[captor_index], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pins[captor_index], LOW);

    /* Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
    unsigned long measure = pulseIn(echo_pins[captor_index], HIGH, MEASURE_TIMEOUT);


    /* Calcul la distance à partir du temps mesuré */
    if (measure == 0)  // timeout expired before getting a response
        return 999999;
    else
        return (((double) measure) * SOUND_SPEED) / 2.0;
}