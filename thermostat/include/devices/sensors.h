#include <DHT.h>
#include <DallasTemperature.h>
#include <./devices/dimmer.h>
#include <DS3231.h>
#include <Wire.h>


// Pin
#define DHTPIN_1 22
#define DS18B20PIN_1 39
#define DS18B20PIN_2 37
#define DHTTYPE DHT21
OneWire warmwire(DS18B20PIN_1);
OneWire coldwire(DS18B20PIN_2);

// Sensors
DHT dht(DHTPIN_1, DHTTYPE);
DallasTemperature warmsensor(&warmwire);
DallasTemperature coldsensor(&coldwire);

// Sensor Address
DeviceAddress warmsensoraddress;
DeviceAddress coldsensoraddress;

// Areas
float targettemperature = 32.0;
float humidtemp = 0.0;
float humidhumd = 0.0;


struct envdata {
  float envtemp = 0.0;
  float envhumd = 0.0;
}enviromentdata;

envdata getEnviromentData(void) {
  envdata data;
  data.envhumd = dht.readHumidity();
  data.envtemp = dht.readTemperature();
  return data;
}

float getWarmData(void) {
  warmsensor.getAddress(warmsensoraddress,0);
  warmsensor.requestTemperatures();
  if (warmsensor.isConnected(warmsensoraddress)) {
    
    if (warmsensor.getTempC(warmsensoraddress) >= targettemperature) {
      setPWM(0);
    } else if ((warmsensor.getTempC(warmsensoraddress) < targettemperature) 
              && (warmsensor.getTempC(warmsensoraddress) >= (targettemperature - 4)) ) {
      setPWM(180);
    } else {
      setPWM(255);
    } 
    return warmsensor.getTempC(warmsensoraddress);
  } else {
    return 99.99;
  }
}

float getColdData(void) {
  coldsensor.getAddress(coldsensoraddress,1);
  coldsensor.requestTemperatures();
  if (coldsensor.isConnected(coldsensoraddress)) {
    return coldsensor.getTempC(coldsensoraddress);
  } else {
    return 99.99;
  }
}