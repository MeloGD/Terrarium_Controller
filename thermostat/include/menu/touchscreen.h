#ifndef touchscreen
#define touchscreen

#include <Arduino.h>
#include <TouchScreen.h>
#include <menu/tft.h>

#define MIN_PRESSURE 100
#define MAX_PRESSURE 1000

/* TouchScreen */
// data pins
//const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int XP = 9, XM = A3, YP = A2 , YM = 8; //320x480 ID=0x9488

// values obtained after touchscreen calibration example, in landscape mode 480 x 320
// const int TS_LEFT = 63, TS_RT = 955, TS_TOP = 892, TS_BOT = 130;
const int TS_LEFT= 129 , TS_RT = 906, TS_TOP = 70, TS_BOT = 958;

//Touch_getXY() updates global vars
int pixel_x, pixel_y;     

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

bool Touch_getXY(void) {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH); 
  bool pressed = (p.z > MIN_PRESSURE && p.z < MAX_PRESSURE);
  if (pressed) {
    //pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    //pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    pixel_x = map(p.y, 70, 958, 0, 480); //.kbv makes sense to me
    pixel_y = map(p.x, 906, 129 , 0, 320);
  }
  return pressed;
}

#endif