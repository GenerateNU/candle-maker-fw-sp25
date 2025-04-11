// add functions here
#include "LCD.h"

static lv_style_t style_header;
LCD::LCD() {}

void LCD::header(void) {
  lv_style_init(&style_header);
  lv_style_set_text_font(&style_header, &lv_font_montserrat_34);
  lv_style_set_text_color(&style_header, lv_color_make(99, 99, 99));

}

static lv_style_t style_body;
void LCD::body(void) {
  lv_style_init(&style_body);
  lv_style_set_text_font(&style_body, &lv_font_montserrat_16);
  lv_style_set_text_color(&style_body, lv_color_black());
}

lv_obj_t *background;
lv_obj_t* LCD::create_background() {
  lv_obj_t *background_box = lv_obj_create(lv_screen_active());
  lv_obj_set_size(background_box, 310, 230);
  lv_obj_set_pos(background_box, 5, 5);

  lv_obj_set_style_radius(background_box, 15, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(background_box, 2, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(background_box, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(background_box, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_clear_flag(background_box, LV_OBJ_FLAG_SCROLLABLE);

  return background_box; 
}

static lv_style_t style_bar;
void LCD::bar_color(void) {
  lv_style_init(&style_bar);
  lv_style_set_bg_color(&style_bar, lv_color_hex(0xFFA500));
  lv_style_set_bg_grad_color(&style_bar, lv_color_hex(0xFFFF00));
  lv_style_set_bg_grad_dir(&style_bar, LV_GRAD_DIR_HOR);
}

lv_obj_t* LCD::draw_candle_icon(lv_obj_t *parent) {
  // Candle icon  container
  lv_obj_t *candle = lv_obj_create(parent);
  lv_obj_set_size(candle, 50, 60);  // More vertical space
  lv_obj_set_style_bg_opa(candle, LV_OPA_TRANSP, LV_PART_MAIN);
  lv_obj_clear_flag(candle, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_border_width(candle, 0, LV_PART_MAIN);

  // layout shit idfk
  lv_obj_set_layout(candle, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(candle, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(candle, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_row(candle, 0, LV_PART_MAIN); // remove spacing between parts

  // FLAME BODY – bottom part of teardrop
  lv_obj_t *flame_body = lv_obj_create(candle);
  lv_obj_set_size(flame_body, 10, 15);
  lv_obj_set_style_radius(flame_body, 10, LV_PART_MAIN);
  lv_obj_set_style_bg_color(flame_body, lv_color_hex(0xFFA500), LV_PART_MAIN);
  lv_obj_set_style_border_width(flame_body, 0, LV_PART_MAIN);
  lv_obj_clear_flag(flame_body, LV_OBJ_FLAG_SCROLLABLE);

  // FLAME TIP – small circle to cap the flame
  lv_obj_t *flame_tip = lv_obj_create(flame_body);
  lv_obj_set_size(flame_tip, 6, 6);
  lv_obj_set_style_radius(flame_tip, LV_RADIUS_CIRCLE, LV_PART_MAIN);
  lv_obj_set_style_bg_color(flame_tip, lv_color_hex(0xFFD700), LV_PART_MAIN); 
  lv_obj_set_style_border_width(flame_tip, 0, LV_PART_MAIN);
  lv_obj_clear_flag(flame_tip, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_align(flame_tip, LV_ALIGN_TOP_MID, 0, -3);

  // Candle body (wax)
  lv_obj_t *body = lv_obj_create(candle);
  lv_obj_set_size(body, 8, 20);
  lv_obj_set_style_radius(body, 2, LV_PART_MAIN);
  lv_obj_set_style_bg_color(body, lv_color_hex(0x888888), LV_PART_MAIN);
  lv_obj_set_style_border_width(body, 0, LV_PART_MAIN);
  lv_obj_clear_flag(body, LV_OBJ_FLAG_SCROLLABLE);

  return candle;
}

void LCD::idle_init()
{
  Serial.println("IDLE screen");
  lv_obj_clean(background);

  lv_obj_t *idle_title = lv_label_create(background);
  lv_obj_add_style(idle_title, &style_header, 0);
  lv_label_set_text(idle_title, "Candle Maker");
  lv_obj_align(idle_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *idle_descr = lv_label_create(background);
  lv_obj_add_style(idle_descr, &style_body, 0);
  lv_label_set_text(idle_descr, "Hello, ready to create\nsome candles?");
  lv_obj_align(idle_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(idle_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *icon = draw_candle_icon(background);
  lv_obj_align_to(icon, idle_descr, LV_ALIGN_TOP_MID, 0, 50);
}

void LCD::heating_init()
{
  Serial.println("HEATING screen");
  lv_obj_clean(background);

  lv_obj_t *heating_title = lv_label_create(background);
  lv_obj_add_style(heating_title, &style_header, 0);
  lv_label_set_text(heating_title, "Heating");
  lv_obj_align(heating_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *heating_descr = lv_label_create(background);
  lv_obj_add_style(heating_descr, &style_body, 0);
  lv_label_set_text(heating_descr, "The machine is warming up the\nwax. Please wait!");
  lv_obj_align(heating_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(heating_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *heat_process = lv_bar_create(background);
  lv_obj_set_size(heat_process, 200, 20);
  lv_obj_align(heat_process, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(heat_process, 0, 7);
  lv_bar_set_value(heat_process, 1, LV_ANIM_OFF);
  lv_obj_add_style(heat_process, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(heat_process, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(heat_process, LV_ALIGN_TOP_MID, 0, 150);
}

void LCD::wick_placement_init()
{
  Serial.println("WICK PLACEMENT screen");
  lv_obj_clean(background);

  lv_obj_t *wick_placement_title = lv_label_create(background);
  lv_obj_add_style(wick_placement_title, &style_header, 0);
  lv_label_set_text(wick_placement_title, "Wick Placement");
  lv_obj_align(wick_placement_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *wick_placement_descr = lv_label_create(background);
  lv_obj_add_style(wick_placement_descr, &style_body, 0);
  lv_label_set_text(wick_placement_descr, "Wick placement in progress...");
  lv_obj_align(wick_placement_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(wick_placement_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *wick_process = lv_bar_create(background);
  lv_obj_set_size(wick_process, 200, 20);
  lv_obj_align(wick_process, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(wick_process, 0, 7);
  lv_bar_set_value(wick_process, 2, LV_ANIM_OFF);
  lv_obj_add_style(wick_process, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(wick_process, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(wick_process, LV_ALIGN_TOP_MID, 0, 150);
}


void LCD::add_oil_init() {
  Serial.println("ADD OIL screen");
  lv_obj_clean(background);

  lv_obj_t *add_oil_title = lv_label_create(background);
  lv_obj_set_style_text_font(add_oil_title, &lv_font_montserrat_24, LV_PART_MAIN);
  lv_label_set_text(add_oil_title, "Personalize Your Candle.");
  lv_obj_set_style_text_align(add_oil_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_align(add_oil_title, LV_ALIGN_TOP_MID, 0, 50);

  lv_obj_t *add_oil_descr = lv_label_create(background);
  lv_obj_add_style(add_oil_descr, &style_body, 0);
  lv_label_set_text(add_oil_descr, "Please pour 1-2 tablespoons of\n your chosen scent oil\n into the funnel.");
  lv_obj_align(add_oil_descr, LV_ALIGN_TOP_MID, 0, 90);
  lv_obj_set_style_text_align(add_oil_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  // should put some image here
}

void LCD::dispensing_init() {
  Serial.println("DISPENSING screen");
  lv_obj_clean(background);

  lv_obj_t *dispensing_title = lv_label_create(background);
  lv_obj_add_style(dispensing_title, &style_header, 0);
  lv_label_set_text(dispensing_title, "Dispensing");
  lv_obj_align(dispensing_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *dispensing_descr = lv_label_create(background);
  lv_obj_add_style(dispensing_descr, &style_body, 0);
  lv_label_set_text(dispensing_descr, "Dispensing hot wax. Please \nexercise caution!");
  lv_obj_align(dispensing_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(dispensing_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *warning = lv_label_create(background);
  lv_label_set_text(warning, LV_SYMBOL_WARNING);
  lv_obj_align(warning, LV_ALIGN_TOP_MID, 0, 120);
  lv_obj_set_style_text_color(warning, lv_color_hex(0xFF0000), LV_PART_MAIN);
  lv_obj_set_style_text_font(warning, &lv_font_montserrat_20, LV_PART_MAIN);

  lv_obj_t *dispensing_progress = lv_bar_create(background);
  lv_obj_set_size(dispensing_progress, 200, 20);
  lv_obj_align(dispensing_progress, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(dispensing_progress, 0, 7);
  lv_bar_set_value(dispensing_progress, 3, LV_ANIM_OFF);
  lv_obj_add_style(dispensing_progress, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(dispensing_progress, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(dispensing_progress, LV_ALIGN_TOP_MID, 0, 150);
}

void LCD::mixing_init() {
  Serial.println("MIXING screen");
  lv_obj_clean(background);

  lv_obj_t *mixing_title = lv_label_create(background);
  lv_obj_add_style(mixing_title, &style_header, 0);
  lv_label_set_text(mixing_title, "Mixing");
  lv_obj_align(mixing_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *mixing_descr = lv_label_create(background);
  lv_obj_add_style(mixing_descr, &style_body, 0);
  lv_label_set_text(mixing_descr, "Blending ingredients for the\n perfect candle!");
  lv_obj_align(mixing_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(mixing_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *mixing_progress = lv_bar_create(background);
  lv_obj_set_size(mixing_progress, 200, 20);
  lv_obj_align(mixing_progress, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(mixing_progress, 0, 7);
  lv_bar_set_value(mixing_progress, 4, LV_ANIM_OFF);
  lv_obj_add_style(mixing_progress, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(mixing_progress, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(mixing_progress, LV_ALIGN_TOP_MID, 0, 150);
}

void LCD::cooling_init() {
  Serial.println("COOLING screen");
  lv_obj_clean(background);

  lv_obj_t *cooling_title = lv_label_create(background);
  lv_obj_add_style(cooling_title, &style_header, 0);
  lv_label_set_text(cooling_title, "Cooling");
  lv_obj_align(cooling_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *cooling_descr = lv_label_create(background);
  lv_obj_add_style(cooling_descr, &style_body, 0);
  lv_label_set_text(cooling_descr, "Cooling down! Please be patient.");
  lv_obj_align(cooling_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(cooling_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *cooling_progress = lv_bar_create(background);
  lv_obj_set_size(cooling_progress, 200, 20);
  lv_obj_align(cooling_progress, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(cooling_progress, 0, 7);
  lv_bar_set_value(cooling_progress, 5, LV_ANIM_OFF);
  lv_obj_add_style(cooling_progress, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(cooling_progress, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(cooling_progress, LV_ALIGN_TOP_MID, 0, 150);
}

void LCD::ejecting_init() {
  Serial.println("EJECTING screen");
  lv_obj_clean(background);

  lv_obj_t *ejecting_title = lv_label_create(background);
  lv_obj_add_style(ejecting_title, &style_header, 0);
  lv_label_set_text(ejecting_title, "Ejecting");
  lv_obj_align(ejecting_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *ejecting_descr = lv_label_create(background);
  lv_obj_add_style(ejecting_descr, &style_body, 0);
  lv_label_set_text(ejecting_descr, "Ejecting candle! Please handle\nwith care.");
  lv_obj_align(ejecting_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(ejecting_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *ejecting_progress = lv_bar_create(background);
  lv_obj_set_size(ejecting_progress, 200, 20);
  lv_obj_align(ejecting_progress, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(ejecting_progress, 0, 7);
  lv_bar_set_value(ejecting_progress, 6, LV_ANIM_OFF);
  lv_obj_add_style(ejecting_progress, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(ejecting_progress, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(ejecting_progress, LV_ALIGN_TOP_MID, 0, 150);
}

void LCD::complete_init() {
  Serial.println("COMPLETE screen");
  lv_obj_clean(background);

  lv_obj_t *complete_title = lv_label_create(background);
  lv_obj_set_style_text_font(complete_title, &lv_font_montserrat_30, LV_PART_MAIN);
  lv_label_set_text(complete_title, "Process Complete.");
  lv_obj_align(complete_title, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *complete_descr = lv_label_create(background);
  lv_obj_add_style(complete_descr, &style_body, 0);
  lv_label_set_text(complete_descr, "You may now remove your candle.\nEnjoy!");
  lv_obj_align(complete_descr, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_style_text_align(complete_descr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  lv_obj_t *complete_progress = lv_bar_create(background);
  lv_obj_set_size(complete_progress, 200, 20);
  lv_obj_align(complete_progress, LV_ALIGN_CENTER, 0, 0);
  lv_bar_set_range(complete_progress, 0, 7);
  lv_bar_set_value(complete_progress, 7, LV_ANIM_OFF);
  lv_obj_add_style(complete_progress, &style_bar, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(complete_progress, lv_color_hex(0x636363), LV_PART_MAIN);
  lv_obj_align(complete_progress, LV_ALIGN_TOP_MID, 0, 150);
}
