#ifndef dimmerguard
#define dimmerguard

#include "rtc.h"
#include "sensors.h"

#define DIMMER_PIN 46
bool day = false;

void setPWM(int pwmvalue) {
  analogWrite(DIMMER_PIN, pwmvalue);
}

void controlWarmTemp(void) {
  DateTime now = rtc.now();
  warm_sensor.getAddress(warm_sensor_address,0);
  warm_sensor.requestTemperatures();
  int hour = now.hour();
  int min = now.minute();
  int up_time = on_uva_hour * 100 + on_uva_minute;
  int current_time = hour * 100 + min;
  int down_time = off_uva_hour * 100 + off_uva_minute;
  if( up_time < current_time && current_time < down_time) {  
    if (warm_sensor.isConnected(warm_sensor_address)) { 
      /*
    // https://reptifiles.com/leopard-gecko-care/leopard-gecko-temperatures-humidity/
      if (warm_sensor.getTempC(warm_sensor_address) >= target_temperature) {
        setPWM(100);
      } else if ((warm_sensor.getTempC(warm_sensor_address) < target_temperature) 
                && (warm_sensor.getTempC(warm_sensor_address) >= (target_temperature - 4)) ) {
        setPWM(110);
      } else {
        setPWM(140);
      }
      */
      setPWM(254);
    }
  } else {
    setPWM(1);
  }
}

#endif