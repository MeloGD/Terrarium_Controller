#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <DHT.h>

// Number of the data pin from the temperature sensor DS18B20
const int data_pin_dq = 8;
// Number of the data pin from them dht22 temp&humidity sensor
const int data_pin_dht = 9;
// Rele digital pin
byte rele_pin = 53;

// Objects OneWire and DallasTemperature for future use with de temp sensor
OneWire temp_onewire(data_pin_dq);
DallasTemperature sensorDS18B20(&temp_onewire);
// Screen object "lcd"
LiquidCrystal_I2C lcd(0x27, 20, 4);
// DHT object
DHT dhtsensor(data_pin_dht, DHT22);

//
DeviceAddress temp_sensor_add_0;
DeviceAddress temp_sensor_add_1;

struct Data {
  float zone0_temp = 0;
  float zone1_temp = 0;
  float zone2_temp = 0;
  float humidity1 = 0;
};


// Functions
const Data GetData(void) {
  Data sensors_data;
  sensorDS18B20.getAddress(temp_sensor_add_0,0);
  sensorDS18B20.getAddress(temp_sensor_add_1,1);
  sensorDS18B20.requestTemperatures();
  if((sensorDS18B20.isConnected(temp_sensor_add_1)) && (sensorDS18B20.isConnected(temp_sensor_add_1))) {
    sensors_data.zone0_temp = sensorDS18B20.getTempC(temp_sensor_add_0);
    sensors_data.zone1_temp = sensorDS18B20.getTempC(temp_sensor_add_1);
    sensors_data.zone2_temp = dhtsensor.readTemperature();
    sensors_data.humidity1 = dhtsensor.readHumidity();
    if (sensors_data.humidity1 > 60) {
        digitalWrite(rele_pin, LOW);
    } else {
      digitalWrite(rele_pin, HIGH);
    }
    return sensors_data;
  }
}

void PrintLCD(const Data sensors_data) {
  lcd.setCursor(4,0);
  lcd.print(sensors_data.zone0_temp);
  lcd.setCursor(10,0);
  lcd.print("grados.");
  //
  lcd.setCursor(4,1);
  lcd.print(sensors_data.zone1_temp);
  lcd.setCursor(10,1);
  lcd.print("grados.");
  //
  lcd.setCursor(4,2);
  lcd.print(sensors_data.zone2_temp);
  lcd.setCursor(10,2);
  lcd.print("grados.");
  //
  lcd.setCursor(4,3);
  lcd.print(sensors_data.humidity1);
  lcd.setCursor(10,3);
  lcd.print("%");
}



void setup() {
  pinMode(rele_pin, OUTPUT);
  sensorDS18B20.begin();
  dhtsensor.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  PrintLCD(GetData());
}
