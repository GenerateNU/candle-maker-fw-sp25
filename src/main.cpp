#include <Arduino.h>
#include <driver/ledc.h>
#include <CMStateMachine.hpp>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "LCD.h"

// Screen Resolution
#define TFT_HOR_RES 240
#define TFT_VER_RES 320

// Buffer size (40 rows)
#define LVGL_BUFFER_SIZE (TFT_HOR_RES * 40)

// LVGL Display Buffer
static lv_draw_buf_t draw_buf;
static lv_color_t buf1[LVGL_BUFFER_SIZE]; // Single buffer

// TFT Display Object
TFT_eSPI tft = TFT_eSPI();

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint16_t w = (area->x2 - area->x1 + 1);
  uint16_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, true);
  tft.endWrite();

  lv_display_flush_ready(disp);
}

// therm pin constant

CMStateMachine stateMachine;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    
  }

  Serial.println("START");
  // analogReadResolution(12);
  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(THERM_PIN, INPUT);
  ledcSetup(heatPwmChannel, 200, 4);
  ledcAttachPin(DRIVE_PIN, heatPwmChannel);

  // screen setup
  tft.begin();
  tft.setRotation(3);
  Serial.println("Set rotation");
  tft.fillScreen(TFT_WHITE);

  int screen_width = (tft.getRotation() % 2 == 0) ? TFT_HOR_RES : TFT_VER_RES;
  int screen_height = (tft.getRotation() % 2 == 0) ? TFT_VER_RES : TFT_HOR_RES;

  lv_init();

  lv_draw_buf_init(&draw_buf, screen_width, 20, LV_COLOR_FORMAT_RGB565, 0, buf1, LVGL_BUFFER_SIZE * sizeof(lv_color_t));

  static lv_display_t *disp;
  disp = lv_display_create(screen_width, screen_height);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, buf1, NULL, LVGL_BUFFER_SIZE * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
  LCD lcd_screen;
  lv_obj_t* background = lcd_screen.create_background();
  lcd_screen.header();
  lcd_screen.body();
  lcd_screen.bar_color();
  //end screen setup

  Serial.println("setup complete");
  delay(10);
  // idle_init();
}

void loop()
{
  lv_timer_handler();
  delay(5);
  Serial.println("LOOP ON");
  int startTime = millis();
  stateMachine.go();
  int endTime = millis();
  stateMachine.nextState();
  Serial.printf("state took %d milliseconds\n", endTime - startTime);
}
