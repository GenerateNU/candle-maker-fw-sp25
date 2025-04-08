// add functions here

#ifndef LCDScreen_h
#define LCDScreen_h

#include "Arduino.h"
#include <TFT_eSPI.h>
#include <lvgl.h>

void idle_init();
void heating_init();
void wick_placement_init();
void add_oil_init();
void dispensing_init();
void mixing_init();
void cooling_init();
void ejecting_init();
void complete_init();


#endif
