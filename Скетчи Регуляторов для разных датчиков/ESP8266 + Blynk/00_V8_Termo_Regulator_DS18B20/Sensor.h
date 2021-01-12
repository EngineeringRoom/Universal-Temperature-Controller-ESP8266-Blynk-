// Обязательно посмотрите это виде #091 Подключение DS18B20 Датчик температуры https://youtu.be/Qq3nzf56esE
// тогда станет все понятнее

// Подключаем библиотеки
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS D4 //PIN куда подключена шина ONE_WIRE (DS18B20)
#define TEMPERATURE_PRECISION 12 // Точность температуры
#define TEMP_SUM 1 // Количество датчиков 

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// Настройка экземпляра oneWire для взаимодействия с любыми устройствами OneWire (а не только с температурными микросхемами Maxim/Dallas)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
// Передаем нашу ссылку oneWire на Даллас Температуру.
DallasTemperature sensors(&oneWire);

// Если раскоментировать то найдется ваш одиночный адрес и скетч заработает
// Но это не совсем правильно.
 //#define SEARCH_DS18B20

// arrays to hold device addresses
// массивы для хранения адресов устройств
// Сюда нужно поместить адрес именно вашего датчика,
// его можно узнать если залить вот этот скетч 03_Single_Dalass_DS18B20
DeviceAddress Thermometer[TEMP_SUM] =
{
  {0x28,0xFF,0xBC,0xCC,0x63,0x16,0x04,0x6B},
};

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
//  Serial.print(" Temp F: ");
//  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

void setupSensor(){
  // Количество датчиков на шине
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  // Определяет тип питания
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

#ifdef SEARCH_DS18B20
          for (int i=0; i<TEMP_SUM; i++)
  {
    if (!sensors.getAddress(Thermometer[i], i))
    Serial.print("Unable to find address for Device ");
    Serial.println(i);
  }    
#endif

// устанавливаем разрешение датчика 9 бит (может быть 9, 10, 11, 12)
// на точность измерения температуры показатель не влияет.
    for (int i=0; i < TEMP_SUM; i++)
  {
    sensors.setResolution(Thermometer[i], TEMPERATURE_PRECISION);
   
    Serial.print("Device 0 Resolution: ");
    Serial.print(sensors.getResolution(Thermometer[i]), DEC); 
    Serial.println();
  }
}//setSetupDS18B20



void loopTempIn1(float &TempIn1)
{
  // По умолчанию тут стоит delay(1000); Но нам это не подходит
  // заменяем на работу с millis();
  if (ms - msTempIn1 > DELAY_TempIn1){
    
  
  sensors.requestTemperatures();
  float TempDS18B20 = sensors.getTempC(Thermometer[0]);

    // Проверка, удалось ли выполнить чтение, и завершить работу если не удолось(чтобы повторить попытку).
    if (TempDS18B20<=-50) {
      Serial.println("Failed to read sensor!");
      Error=true;
      return;
    }
   
    Serial.print("Temperature: ");
    Serial.print(TempDS18B20);
    Serial.println(" *C ");
    
    TempIn1=TempDS18B20;

//  Это незаконченная заготовка для обработки нескольких дачиков
//  for (int i=0; i < TEMP_SUM; i++)
//  {TempDS18B20[i]= int(sensors.getTempC(Thermometer[i]));}

    msTempIn1 = ms;  
  }//if (ms - msTempIn1 > DELAY_TempIn1)
}
