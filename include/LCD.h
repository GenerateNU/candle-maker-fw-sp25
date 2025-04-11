// add functions here

#ifndef LCD_h
#define LCD_h

#include "Arduino.h"
#include <TFT_eSPI.h>
#include <lvgl.h>

class LCD {
    public: 
        void header();
        void body();
        void bar_color();

        void idle_init();
        void heating_init();
        void wick_placement_init();
        void add_oil_init();
        void dispensing_init();
        void mixing_init();
        void cooling_init();
        void ejecting_init();
        void complete_init();

        lv_obj_t* create_background();
        lv_obj_t* draw_candle_icon(lv_obj_t *parent);
        lv_obj_t* background;

};

#endif
