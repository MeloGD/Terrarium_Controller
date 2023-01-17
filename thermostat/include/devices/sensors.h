#ifndef sensors
#define sensors

#include <DHT.h>
#include <DallasTemperature.h>
//#include <devices/dimmer.h>
#include <devices/rtc.h>

// Pin
#define DHT_PIN_1 24
#define DHT_PIN_2 26
#define DS18B20_PIN_1 28
#define DS18B20_PIN_2 30
#define DHT_TYPE DHT21
OneWire warm_wire(DS18B20_PIN_1);
OneWire cold_wire(DS18B20_PIN_2);

// Sensors
DHT dht_env(DHT_PIN_1, DHT_TYPE);
DHT dht_hum(DHT_PIN_2, DHT_TYPE);
DallasTemperature warm_sensor(&warm_wire);
DallasTemperature cold_sensor(&cold_wire);

// Sensor Address
DeviceAddress warm_sensor_address;
DeviceAddress cold_sensor_address;

float target_temperature = 32.0;

struct envdata {
  float temp = 0.0;
  float humd = 0.0;
}enviromentdata;

envdata getEnviromentData(void) {
  envdata data;
  data.humd = dht_env.readHumidity();
  data.temp = dht_env.readTemperature();
  return data;
}

envdata getHumidData(void) {
  envdata data;
  data.humd = dht_hum.readHumidity();
  data.temp = dht_hum.readTemperature();
  return data;
}

float getWarmData(void) {
  warm_sensor.getAddress(warm_sensor_address,0);
  warm_sensor.requestTemperatures();
  if (warm_sensor.isConnected(warm_sensor_address)) {
    return warm_sensor.getTempC(warm_sensor_address);
  } else {
    return 99.99;
  }
}

float getColdData(void) {
  cold_sensor.getAddress(cold_sensor_address,1);
  cold_sensor.requestTemperatures();
  if (cold_sensor.isConnected(cold_sensor_address)) {
    return cold_sensor.getTempC(cold_sensor_address);
  } else {
    return 99.99;
  }
}

#endif