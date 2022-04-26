#ifndef touchscreen
#define touchscreen

#include <Arduino.h>
#include <TouchScreen.h>
#include <menu/tft.h>

#define MINPRESSURE 100
#define MAXPRESSURE 1000

/* TouchScreen */
// data pins
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341

// values obtained after touchscreen calibration example, in landscape mode 480 x 320
const int TS_LEFT = 956, TS_RT = 172, TS_TOP = 225, TS_BOT = 878;

//Touch_getXY() updates global vars
int pixel_x, pixel_y;     

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

bool Touch_getXY(void) {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH); 
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
  }
  return pressed;
}

#endif