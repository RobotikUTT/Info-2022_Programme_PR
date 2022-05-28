//
// Created by thgir on 25/05/2022.
//

#include "displayer.h"
#include "pins.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

void init_lcd() {
    lcd.init();
    lcd.backlight();
}

void display_score(const uint8_t score) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Robotik UTT");
    lcd.setCursor(4, 1);
    lcd.print(score);
}