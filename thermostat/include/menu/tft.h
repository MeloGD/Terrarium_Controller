#ifndef tftcustom
#define tftcustom

#include <MCUFRIEND_kbv.h>
#include <devices/sensors.h>
#include <devices/rtc.h>

// Colors
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEFtft
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

// tft object using the analog pins  LCD_CS = A3, LCD_CD = A2, LCD_WR = A1, LCD_RD = A0, LCD_RESET = A4 for spi comminication
MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);

void launchTFT(void) {
  // The id is required for the tft to work
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.fillScreen(BLACK);
  // I had to use this function in order to see the colors right
  tft.invertDisplay(true);
  // 0 -> 0º, 1 -> 90º, 2 -> 180, 3 -> 270
  tft.setRotation(1);
}

void printTFTClock(void) {
  DateTime now = rtc.now();
  tft.setTextSize(3);
  tft.setTextColor(WHITE,BLACK);
  tft.setCursor(300, 10);
  if (now.hour() < 10) {
    tft.print('0');
  }
  tft.print(now.hour(), DEC);
  tft.setCursor(340, 10);
  tft.print(":");
  tft.setCursor(360, 10);
  if (now.minute() < 10) {
    tft.print('0');
  }
  tft.print(now.minute());
  tft.setCursor(400, 10);
  tft.print(":");
  tft.setCursor(420, 10);
  if (now.second() < 10) {
    tft.print('0');
  }
  tft.print(now.second(), DEC);
}

void loadEnviroment() {
  printTFTClock();
  tft.setCursor(10,10);
  tft.print("Enviroment"); 
  tft.setCursor(60, 75);
  tft.setTextSize(2);
  tft.print("Temperature");
  tft.setCursor(300, 75);
  tft.setTextSize(2);
  tft.print("Humidity");
  tft.drawRoundRect(40, 100, 180, 140, 10, WHITE);
  tft.setCursor(70,150);
  tft.setTextSize(3);
  tft.print(getEnviromentData().temp);
  tft.print(" C");
  tft.drawRoundRect(260, 100, 180, 140, 10, WHITE);
  tft.setCursor(295,150);
  //tft.setTextSize(5);
  tft.print(getEnviromentData().humd);
  tft.print(" %");
}

void loadWarmHide(void) {
  //printTFTClock();
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Warm Hide");
  tft.setCursor(60, 75);
  tft.setTextSize(2);
  tft.print("Actual Temp.");
  tft.drawRoundRect(40, 100, 180, 140, 10, WHITE);
  tft.setCursor(275, 75);
  tft.setTextSize(2);
  tft.print("Target Temp.");
  tft.drawRoundRect(260, 100, 180, 140, 10, WHITE);
  tft.setCursor(290,150);
  tft.setTextSize(3);
  tft.print(target_temperature);
  tft.print(" C");
}

void loadHumidHide(void) {
  printTFTClock();
  tft.setCursor(10,10);
  //tft.setTextSize(3);
  //tft.setTextColor(WHITE);
  tft.print("Humid Hide");
  tft.setCursor(60, 75);
  tft.setTextSize(2);
  tft.print("Temperature");
  tft.setCursor(300, 75);
  tft.setTextSize(2);
  tft.print("Humidity");
  tft.drawRoundRect(40, 100, 180, 140, 10, WHITE);
  tft.setCursor(70,150);
  tft.setTextSize(3);
  tft.print(getHumidData().temp);
  tft.print(" C");
  tft.drawRoundRect(260, 100, 180, 140, 10, WHITE);
  tft.setCursor(295,150);
  tft.print(getHumidData().humd);
  tft.print(" %");
}
void loadColdHide(void) {
  float temp = getColdData();
  printTFTClock();
  tft.setCursor(10,10);
  //tft.setTextSize(3);
  //tft.setTextColor(WHITE,BLACK);
  tft.print("Cold Hide");
  tft.setCursor(172, 75);
  tft.setTextSize(2);
  tft.print("Temperature");
  tft.drawRoundRect(150, 100, 180, 140, 10, WHITE);
  tft.setCursor(180,150);
  tft.setTextSize(3);
  tft.print(temp);
  tft.print(" C");
}
void loadLightsPanel(void) {
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Lights Control Panel");
  tft.setTextSize(3);
  tft.setCursor(40,80);
  tft.print("DHP");
  tft.setCursor(40,130);
  tft.print("UVB");
  tft.setCursor(40,180);
  tft.print("Plants");
}

void loadEditTempMenu() {
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Set a new target");
  tft.setCursor(10,40);
  tft.print("temperature value");
  tft.setTextSize(2);
  tft.setCursor(20,160);
  tft.print("New target temp.");
  tft.drawRoundRect(270, 100, 180, 140, 10, WHITE);
  tft.setCursor(290,155);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(3);
  tft.print(target_temperature);
  tft.print(" ");
  tft.print("\367");
  tft.print("C");
}


// DHP
void loadEditTimeHeatMenu(void) {
  //printTFTClock();
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, BLACK);
  tft.print("Set DHP Time");
  tft.setTextSize(2);
  tft.setCursor(20,100);  
  tft.print("Switch on at:");
  tft.setCursor(20,200);  
  tft.print("Switch off at:");
  //
  tft.setTextSize(2);
  tft.setCursor(245,60);
  tft.print("Hrs.");
  tft.setCursor(385,60);
  tft.print("Min.");
  tft.setCursor(245,160);
  tft.print("Hrs.");
  tft.setCursor(385,160);
  tft.print("Min.");
  //switch on
  tft.setTextSize(3);
  tft.setCursor(247,100);
  tft.print(on_dhp_hour);
  tft.drawRoundRect(240, 85, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,100);
  tft.print(on_dhp_minute);
  tft.drawRoundRect(380, 85, 50, 50, 10, WHITE);
  // switch off
  tft.setTextSize(3);
  tft.setCursor(247,200);
  tft.print(off_dhp_hour);
  tft.drawRoundRect(240, 185, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,200);
  tft.print(off_dhp_minute);
  tft.drawRoundRect(380, 185, 50, 50, 10, WHITE);
}

//UVB
void loadEditTimeUvbMenu(void) {
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, BLACK);
  tft.print("Set UVB Time");
  tft.setTextSize(2);
  tft.setCursor(20,100);  
  tft.print("Switch on at:");
  tft.setCursor(20,200);  
  tft.print("Switch off at:");
  //
  tft.setTextSize(2);
  tft.setCursor(245,60);
  tft.print("Hrs.");
  tft.setCursor(385,60);
  tft.print("Min.");
  tft.setCursor(245,160);
  tft.print("Hrs.");
  tft.setCursor(385,160);
  tft.print("Min.");
  //switch on
  tft.setTextSize(3);
  tft.setCursor(247,100);
  tft.print(on_uvb_hour);
  tft.drawRoundRect(240, 85, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,100);
  tft.print(on_uvb_minute);
  tft.drawRoundRect(380, 85, 50, 50, 10, WHITE);
  // switch off
  tft.setTextSize(3);
  tft.setCursor(247,200);
  tft.print(off_uvb_hour);
  tft.drawRoundRect(240, 185, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,200);
  tft.print(off_uvb_minute);
  tft.drawRoundRect(380, 185, 50, 50, 10, WHITE);
}

// Plants
void loadEditTimePlantsMenu(void) {
  tft.setCursor(10,10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, BLACK);
  tft.print("Set Plants Time");
  tft.setTextSize(2);
  tft.setCursor(20,100);  
  tft.print("Switch on at:");
  tft.setCursor(20,200);  
  tft.print("Switch off at:");
  //
  tft.setTextSize(2);
  tft.setCursor(245,60);
  tft.print("Hrs.");
  tft.setCursor(385,60);
  tft.print("Min.");
  tft.setCursor(245,160);
  tft.print("Hrs.");
  tft.setCursor(385,160);
  tft.print("Min.");
  //switch on
  tft.setTextSize(3);
  tft.setCursor(247,100);
  tft.print(on_plants_hour);
  tft.drawRoundRect(240, 85, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,100);
  tft.print(on_plants_minute);
  tft.drawRoundRect(380, 85, 50, 50, 10, WHITE);
  // switch off
  tft.setTextSize(3);
  tft.setCursor(247,200);
  tft.print(off_plants_hour);
  tft.drawRoundRect(240, 185, 50, 50, 10, WHITE);
  tft.setTextSize(3);
  tft.setCursor(387,200);
  tft.print(off_plants_minute);
  tft.drawRoundRect(380, 185, 50, 50, 10, WHITE);
}
#endif