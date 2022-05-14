#ifndef relay
#define relay

#include <menu/tft.h>
#include <DS3231.h>
#include <Wire.h>

//relay
byte dhp_relay_pin = 40;
byte uvb_relay_pin = 42;
byte light_relay_pin = 44;

void relayControlLights(void) {
  DateTime now =  rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  // UVB
  if ((hour == on_uvb_hour) && (minute == on_uvb_minute)) {
    digitalWrite(uvb_relay_pin, LOW);
  } else if ((hour == off_uvb_hour) && (minute == off_uvb_minute)){
    digitalWrite(uvb_relay_pin, HIGH);
  }
  // Plants Light
  if ((hour == on_plants_hour) && (minute == on_plants_minute)) {
    digitalWrite(light_relay_pin, LOW);
  } else if ((hour == off_plants_hour) && (minute == off_plants_minute)){
    digitalWrite(light_relay_pin, HIGH);
  }
}

#endif