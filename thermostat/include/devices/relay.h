#ifndef relay
#define relay

#include <menu/tft.h>
#include <DS3231.h>
#include <Wire.h>

//relay
#define DHP_RELAY_PIN 32
#define UVB_RELAY_PIN 34
#define LIGHT_RELAY_PIN 36

void relayControlLights(void) {
  DateTime now =  rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  // UVB
  if ((hour == on_uvb_hour) && (minute == on_uvb_minute)) {
    digitalWrite(UVB_RELAY_PIN, LOW);
  } else if ((hour == off_uvb_hour) && (minute == off_uvb_minute)){
    digitalWrite(UVB_RELAY_PIN, HIGH);
  }
  // Plants Light
  if ((hour == on_plants_hour) && (minute == on_plants_minute)) {
    digitalWrite(LIGHT_RELAY_PIN, LOW);
  } else if ((hour == off_plants_hour) && (minute == off_plants_minute)){
    digitalWrite(LIGHT_RELAY_PIN, HIGH);
  }
}

#endif