#include <DHT.h>
#include <DallasTemperature.h>
#include <./devices/relay.h>
#include <./devices/dimmer.h>
#include <./devices/rtc.h>

// Pin
OneWire warmwire(39);
OneWire coldwire;

// Sensors
DallasTemperature warmsensor(&warmwire);
DallasTemperature coldsensor(&coldwire);

// Sensor Address
DeviceAddress warmsensoraddress;
DeviceAddress coldsensoraddress;

// Areas
float envtemp = 0.0;
float envhumd = 0.0;
float warmtemp = 0.0;
float humidtemp = 0.0;
float humidhumd = 0.0;
float coldtemp = 0.0;

float getWarmData(void) {
  warmsensor.getAddress(warmsensoraddress,0);
  warmsensor.requestTemperatures();
  if (warmsensor.isConnected(warmsensoraddress)) {
    
    if (warmsensor.getTempC(warmsensoraddress) >= 32) {
      setPWM(0);
    } else if ((warmsensor.getTempC(warmsensoraddress) < 32) && (warmsensor.getTempC(warmsensoraddress) >= 28) ) {
      setPWM(180);
    } else {
      setPWM(255);
    } 
    return warmsensor.getTempC(warmsensoraddress);
  } else {
    return 99.99;
  }
}