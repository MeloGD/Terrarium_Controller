#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

// Number of the data pin from the temperature sensor DS18B20
const int data_pinDQ = 8;

// Objects OneWire and DallasTemperature for future use with de temp sensor
OneWire temp_onewire(data_pinDQ);
DallasTemperature sensorDS18B20(&temp_onewire);
// Screen object "lcd"
LiquidCrystal_I2C lcd(0x27,20,4);

DeviceAddress temp_sensor_add_0;
DeviceAddress temp_sensor_add_1;


struct Temperature_Data {
  float zone0 = 0;
  float zone1 = 0;
};


// Functions
const Temperature_Data GetTemperature(void) {
  Temperature_Data temperatures;
  sensorDS18B20.getAddress(temp_sensor_add_0,0);
  sensorDS18B20.getAddress(temp_sensor_add_1,1);
  sensorDS18B20.requestTemperatures();
  if((sensorDS18B20.isConnected(temp_sensor_add_1)) && (sensorDS18B20.isConnected(temp_sensor_add_1))) {
    temperatures.zone0 = sensorDS18B20.getTempC(temp_sensor_add_0);
    temperatures.zone1 = sensorDS18B20.getTempC(temp_sensor_add_1);
    //float temps = sensorDS18B20.getTempCByIndex(0);
    //float temp
    //float temp = sensorDS18B20.getTempC(temp_sensor_add);
    return temperatures;
  }
}

void PrintLCD(const Temperature_Data temperature) {
  lcd.setCursor(4,0);
  lcd.print(temperature.zone0);
  lcd.setCursor(10,0);
  lcd.print("grados.");
  //
  lcd.setCursor(4,1);
  lcd.print(temperature.zone1);
  lcd.setCursor(10,1);
  lcd.print("grados.");

}

void setup() {
  sensorDS18B20.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  PrintLCD(GetTemperature());
}
