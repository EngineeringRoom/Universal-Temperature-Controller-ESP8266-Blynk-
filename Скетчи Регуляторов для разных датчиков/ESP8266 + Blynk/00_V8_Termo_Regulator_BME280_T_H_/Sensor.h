// Датчик Температуры, Влажности и Давления:
// GY-BME280-3.3 (3.78 $)https://goo.gl/T95nQ5
// Измеряет температуру -40…+85
//*************************************************************************
// Библиотека Adafruit Unified Sensor Driver // https://github.com/adafruit/Adafruit_Sensor.git
// "Adafruit_BME280.h"                       // https://github.com/adafruit/Adafruit_BME280_Library.git

// BME 280
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//  Подключается BME 280 по I2C:
//  Плата ESP-12E подключаем SCL - D1(GPIO5) // SDA - D2(GPIO4)
//  Плата Arduino UNO (NANO) SCL - А5 // SDA - А4

 // Если по SPI то вот для Ардуины
//#define BME_SCK 13
//#define BME_MISO 12
//#define BME_MOSI 11
//#define BME_CS 10

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI


void setupSensor() {
  Serial.print("BME280 begin!");
 
    bool status;
   
// Здесь вводим адрес устройства
// По умолчанию адрес i2c равен 0x77. 
// Если вы добавите перемычку из SDO в V3.3, адрес изменится на 0x77.
// Если вы добавите перемычку из SDO в GND, адрес изменится на 0x76.
    status = bme.begin(0x76);  
    if (!status) {
        Serial.print("Could not find a valid BME280 sensor, check wiring!");
        Error=true;
        return;
        
    }
    bme.setSampling();

  Serial.println("  Done!");  
}

void loopTempIn1(float &TempIn1) {
  // По умолчанию тут стоит delay(1000); Но нам это не подходит
  // заменяем на работу с millis();
  if (ms - msTempIn1 > DELAY_TempIn1){
  
// Температура
    float TempBME280=bme.readTemperature();
    float HumidBME280=bme.readHumidity();

    // Проверка, удалось ли выполнить чтение, и завершить работу если не удолось(чтобы повторить попытку).
    if (TempBME280<=-50) {
      Serial.println("Failed to read sensor!");
      Error=true;
      return;
    }
        
    Serial.print("Temperature: ");Serial.print(TempBME280);Serial.println(" *C ");
    Serial.print("Humidity: ");Serial.print(HumidBME280);Serial.println(" % ");
    
    
    TempIn1=TempBME280;
    HumidIn1=HumidBME280;
    
  msTempIn1 = ms;  
  }//if (ms - msTempIn1 > DELAY_TempIn1)
}
