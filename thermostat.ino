#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

// Number of the data pin from the temperature sensor DS18B20
const int data_pinDQ = 8;

// Objects OneWire and DallasTemperature for future use with de temp sensor
OneWire temp_onewire(data_pinDQ);
DallasTemperature sensorDS118B20(&temp_onewire);
// Screen object "lcd"
LiquidCrystal_I2C lcd(0x27,20,4);

DeviceAddress temp_sensor_add;


// Functions
const float GetTemperature(void) {
  sensorDS118B20.getAddress(temp_sensor_add,0);
  sensorDS118B20.requestTemperatures();
  if(sensorDS118B20.isConnected(temp_sensor_add)){
    //Serial.println(sensorDS118B20.getTempCByIndex(0));
    float temp = sensorDS118B20.getTempC(temp_sensor_add);
    return temp;
  }
}

void PrintLCD(const float temperature) {
  lcd.setCursor(4,1);
  lcd.print(temperature);
  lcd.setCursor(10,1);
  lcd.print("grados.");
}

void setup() {
  sensorDS118B20.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  PrintLCD(GetTemperature());
}
