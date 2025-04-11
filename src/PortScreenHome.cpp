#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "PortScreenHome.h"
#include "colors.h"
#include "driver/i2c.h"


// Global variables
int currentValue = 0;
int lastValue = -1; // Tracks the last value to avoid unnecessary redraws


void displayBeatingScreen(TFT_eSPI &tft) {
    
    tft.setRotation(0);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_BEIGE); // Background color
    // Draw the Brown Circular Border
    int outerRadius = 120;  // Outer radius of the circle
    int innerRadius = 110;  // Reduced inner radius for a thicker border
    tft.fillCircle(120, 120, outerRadius, COLOR_BROWN); // Draw the outer circle
    tft.fillCircle(120, 120, innerRadius, COLOR_LIGHT_BROWN); // Cut out the inner circle
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Fitolux."
    tft.setTextColor(COLOR_BLACK, COLOR_LIGHT_BROWN);
    tft.drawString("Fitolux.", (240 - tft.textWidth("Fitolux.")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Methods", (240 - tft.textWidth("Methods")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("SELECT AMOUNT", (240 - tft.textWidth("SELECT AMOUNT")) / 2, 110);

    // Battery Percentage
    tft.setFreeFont(&FreeSans9pt7b); // Smaller font for battery
    tft.setTextColor(COLOR_BLACK, COLOR_LIGHT_BROWN);
    String batteryText = "Battery: " + String(10) + "%";
    tft.drawString(batteryText, (240 - tft.textWidth(batteryText)) / 2 - 5, 135); // Slight adjustment to the left

    // Input Box
    int boxWidth = 160; // Adjusted width
    int boxHeight = 40; // Adjusted height
    int boxX = (240 - boxWidth) / 2;
    int boxY = 160;
    tft.fillRoundRect(boxX, boxY, boxWidth, boxHeight, 20, COLOR_BROWN); // Fully rounded rectangle

    // Unit Text ("G")
    tft.setTextColor(COLOR_BLACK, COLOR_BROWN);
    tft.setFreeFont(&FreeSans12pt7b);
    tft.drawString("G", boxX + boxWidth - 30, boxY + (boxHeight - 16) / 2);
}
void updateValue(TFT_eSPI tft, int value, int battery) {
    int boxWidth = 160;
    int boxHeight = 40;
    int boxX = (240 - boxWidth) / 2;
    int boxY = 160;

    // Clear the previous value
    tft.fillRect(boxX + 20, boxY + (boxHeight - 16) / 2, 120, 20, COLOR_BROWN); // Clear value area

    // Draw the new value
    tft.setTextColor(COLOR_BLACK, COLOR_BROWN);
    tft.setFreeFont(&FreeSans12pt7b);
    tft.drawString(String(value), boxX + (boxWidth / 2) - (tft.textWidth(String(value)) / 2), boxY + (boxHeight - 16) / 2);

    // Clear and redraw battery percentage
    tft.fillRect(0, 135, 240, 20, COLOR_LIGHT_BROWN); // Clear battery area
    tft.setTextColor(COLOR_BLACK, COLOR_LIGHT_BROWN);
    tft.setFreeFont(&FreeSans9pt7b);
    String batteryText = "Battery: " + String(battery) + "%";
    tft.drawString(batteryText, (240 - tft.textWidth(batteryText)) / 2 - 5, 135); // Slight adjustment to the left
}

// void loop() {
//     // Simulate value changes
//     currentValue = (currentValue + 1) % 100; // Increment value and loop back to 0 after 99
//     if (currentValue != lastValue) {
//         updateValue(currentValue); // Update only the value area
//         lastValue = currentValue;  // Track the last value to avoid redundant updates
//     }
//     delay(100); // Small delay for smooth updates
// }


void displayBasicScreen(TFT_eSPI &tft) {
    
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_BEIGE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Make your dumbass candle", (240 - tft.textWidth("Make your dumbass candle")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("PRESS START", (240 - tft.textWidth("PRESS START")) / 2, 110);
}

void displayHeatingScreen(TFT_eSPI &tft) {
    
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_WHITE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that shit warm", (240 - tft.textWidth("Let that shit warm")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("HEATING", (240 - tft.textWidth("HEATING")) / 2, 110);
}

void displayDispensingScreen(TFT_eSPI &tft){
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_BEIGE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that shit dispense", (240 - tft.textWidth("Let that shit dispense")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("DISPENSE", (240 - tft.textWidth("DISPENSE")) / 2, 110);
}

void displayMixingScreen(TFT_eSPI &tft){
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_WHITE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that shit mix", (240 - tft.textWidth("Let that shit mix")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("MIXING", (240 - tft.textWidth("MIXING")) / 2, 110);
}

void displayWickPlacementScreen(TFT_eSPI &tft){
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_WHITE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that wick place", (240 - tft.textWidth("Let that wick place")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("WICK PLACEMENT", (240 - tft.textWidth("WICK PLACEMENT")) / 2, 110);
}

void displayCoolingScreen(TFT_eSPI &tft){
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_WHITE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that shit cool", (240 - tft.textWidth("Let that shit cool")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("COOLING", (240 - tft.textWidth("COOLING")) / 2, 110);
}

void displayEjectingScreen(TFT_eSPI &tft){
    tft.setRotation(90);     // Set rotation (adjust as necessary)
    tft.fillScreen(COLOR_WHITE); // Background color
    // Header Section
    tft.setFreeFont(&FreeSansBold18pt7b); // Font for "Candle Maker"
    tft.setTextColor(COLOR_BLACK);
    tft.drawString("Candle Maker", (240 - tft.textWidth("Candle Maker")) / 2, 30);
    tft.setFreeFont(&FreeSans9pt7b); // Font for "Methods"
    tft.drawString("Let that shit eject", (240 - tft.textWidth("Let that shit eject")) / 2, 70);
    // Main Section - "SELECT AMOUNT"
    tft.setFreeFont(&FreeSans12pt7b); // Font for "SELECT AMOUNT"
    tft.drawString("EJECTING", (240 - tft.textWidth("EJECTING")) / 2, 110);
}