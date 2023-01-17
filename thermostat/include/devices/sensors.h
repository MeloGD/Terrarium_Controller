#ifndef sensors
#define sensors

#include <DHT.h>
#include <DallasTemperature.h>
#include <devices/dimmer.h>
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

// Areas
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
    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    bool day;
    // https://reptifiles.com/leopard-gecko-care/leopard-gecko-temperatures-humidity/
    if (on_dhp_hour  <= hour < off_dhp_hour) {
      day = true;
    } else {
      day = false;
    }
    if (day) {
      if (warm_sensor.getTempC(warm_sensor_address) >= target_temperature) {
        setPWM(0);
      } else if ((warm_sensor.getTempC(warm_sensor_address) < target_temperature) 
                && (warm_sensor.getTempC(warm_sensor_address) >= (target_temperature - 4)) ) {
        setPWM(180);
      } else {
        setPWM(255);
      } 
      return warm_sensor.getTempC(warm_sensor_address);
    } else if (!day) {  // Night
      if (warm_sensor.getTempC(warm_sensor_address) >= (target_temperature - 8)) {
        setPWM(0);
      } else if ((warm_sensor.getTempC(warm_sensor_address) < (target_temperature - 8)) 
                && (warm_sensor.getTempC(warm_sensor_address) >= (target_temperature - 10)) ) {
        setPWM(180);
      } else {
        setPWM(255);
      } 
      return warm_sensor.getTempC(warm_sensor_address);
    }
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