#ifndef rtcguard
#define rtcguard

#include <DS3231.h>
#include <Wire.h>

//rtc
RTClib rtc;

// variables
int menu_index = 0;

int on_uva_hour = 8;
int on_uva_minute = 0;
int off_uva_hour = 21;
int off_uva_minute = 15;

int on_uvb_hour = 9;
int on_uvb_minute = 0;
int off_uvb_hour = 15;
int off_uvb_minute = 30;

int on_plants_hour = 9;
int on_plants_minute = 30;
int off_plants_hour = 20;
int off_plants_minute = 0;


#endif