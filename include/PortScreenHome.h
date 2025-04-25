#pragma once

#ifndef _PORT_SCREEN_H
#define _PORT_SCREEN_H
#include <TFT_eSPI.h>
#include <Arduino.h>


// Declare external TFT object to ensure no redefinition
extern TFT_eSPI tft;
extern int batteryLevel;
// Function declarations
// void displayStartScreen();
void displayBeatingScreen(TFT_eSPI &tft);
void updateValue(TFT_eSPI tft, int value, int battery);
void displayBasicScreen(TFT_eSPI &tft);
void displayHeatingScreen(TFT_eSPI &tft);
void displayDispensingScreen(TFT_eSPI &tft);
void displayMixingScreen(TFT_eSPI &tft);
void displayWickPlacementScreen(TFT_eSPI &tft);
void displayCoolingScreen(TFT_eSPI &tft);
void displayEjectingScreen(TFT_eSPI &tft);
// void updateWeightDisplay(int weight);
// void drawDispensingScreen();
// void drawCompleteScreen();
#endif