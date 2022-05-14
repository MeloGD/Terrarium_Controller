#ifndef rtcguard
#define rtcguard

#include <DS3231.h>
#include <Wire.h>

//rtc
RTClib rtc;

// variables
int menu_index = 0;

int on_dhp_hour = 8;
int on_dhp_minute = 0;
int off_dhp_hour = 20;
int off_dhp_minute = 0;

int on_uvb_hour = 9;
int on_uvb_minute = 00;
int off_uvb_hour = 19;
int off_uvb_minute = 30;

int on_plants_hour = 9;
int on_plants_minute = 30;
int off_plants_hour = 20;
int off_plants_minute = 00;


#endif