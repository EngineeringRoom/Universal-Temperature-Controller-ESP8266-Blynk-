/*
 * Логика работы.
 * Заполните осмысленными названиями Массив NamesOut[sumRegul]
 * Разкомментируйте #define SEARCH_DS18B20
 * Залейте скетч.
 * Благодаря этому вы найдете адреса своих датчиков.
 * Нагревая (рукой к примеру) определите какой датчик соответствует какому названию
 * Заполните массив Thermometer[TEMP_SUM] в нужном порядке что бы соответствовали
 * названия и номер датчика. Физически дайте метки датчикам (бирки навешайте).
 * Закомментируйте #define SEARCH_DS18B20
 * Залейте скетч еще раз. И проверьте все ли правильно.
 * Теперь откопируйте массив Thermometer[TEMP_SUM] в основной скетч
 */
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4
#define TEMP_SUM 4 // Количество датчиков

  // устанавливаем разрешение датчика 9 бит (может быть 9, 10, 11, 12)
  // на точность измерения температуры показатель не влияет. 
 #define TEMPERATURE_PRECISION 12
const int sumRegul = TEMP_SUM;

// Настройка экземпляра oneWire для взаимодействия с любыми устройствами OneWire (а не только с температурными микросхемами Maxim/Dallas)
OneWire oneWire(ONE_WIRE_BUS);

// Передаем нашу ссылку oneWire на Даллас Температуру.
DallasTemperature sensors(&oneWire);

// Если #define SEARCH_DS18B20 раскоментирован то ищим Термометры и грубо говоря затераем новыми
// адресами массив адресов DeviceAddress Thermometer[TEMP_SUM]
// то есть то что ниже вы определите массив адресов на порядок
// отоброжения датчиков влиять не будет, они будут в том
// порядке в котором они найдуться. Вот.
 #define SEARCH_DS18B20

// массивы для хранения адресов устройств
DeviceAddress Thermometer[TEMP_SUM] =
{
  {0x28,0xFF,0xA0,0x7E,0x64,0x16,0x03,0x59},
  {0x28,0xFF,0xAC,0x30,0xA1,0x16,0x05,0x36},  
  {},
  {},
  
};

// Название реле (терморегуляторов)
String NamesOut[sumRegul] = {
                              "Баня",
                              "Дом",
                              "Гараж",
                              "Подвал",
                            };

//**********************************************************
// Функции
 
// Вывод в сериал температуру
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
}

// Вывод в сериал адресса
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void setup()
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

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
}//setup()

void loop()
{ 

  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // It responds almost immediately. Let's print out the data
   for (int i=0; i < TEMP_SUM; i++)
    {
      Serial.print(NamesOut[i]);    // Название датчика
      Serial.print(" ");      
      printAddress(Thermometer[i]); // Адрес датчика
      Serial.print(" ");
      printTemperature(Thermometer[i]); // Температура датчика
      Serial.println();
    }
  Serial.println();
  delay(1000);
}
