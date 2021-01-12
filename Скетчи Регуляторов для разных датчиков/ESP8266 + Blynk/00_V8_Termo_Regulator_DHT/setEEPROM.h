/*
 Справка
  addr - адрес байта
  size - Размер данных должен быть в диапазоне от 4 до 4096 байт.
 EEPROM.begin(size);          // Каждый раз объявляем если хотим прочесть или записать для ESP
 EEPROM.write(addr,  val);   // записали переменную val(размером int8_t) по адресу addr 
 EEPROM.read(addr,  val);    // прочитать из адреса addr в переменную val(размером int8_t)

// Внимание Размеры должны совпадать иначе могут быть проблемы
// записали число val(библиотека "EEPROMAnything.h" размер определит сама) по адресу addr
 EEPROM_writeAnything(addr, val);
// прочитать из адреса addr в переменную val(библиотека "EEPROMAnything.h" размер определит сама) 
 EEPROM_readAnything(addr, val);  
  
 EEPROM.commit();        // закончить запись
 EEPROM.end(); тоже производит запись данных,
 а также освобождает оперативную память от данных,
 запись которых произведена.

   Размеры переменных
   8бит = 1 байт
   u - перед int значит что число положительное
   
 int8_t     |  char                |   от -128 до 127               | 1 byte
 uint8_t    |  byte, unsigned char |   от 0 до 255                  | 1 byte
 int16_t    |  int                 |   от -32768 до 32767           | 2 byte
 uint16_t   |  unsigned int, word  |   от 0 до 65535                | 2 byte
 int32_t    |  long                |  от  -2147483648 до 2147483647 | 4 byte
 uint32_t   |  unsigned long       |  от 0 до 4294967295            | 4 byte
 
 и еще бывают int64_t и  uint64_t
*/

#include <EEPROM.h>
#include "EEPROMAnything.h" // http://playground.arduino.cc/Code/EEPROMWriteAnything

 
  bool Recorded;  // Служит для перезаписи заводских настроек (Factory Settings)
  int addr = 0;   // Начальный адрес EEPROM
  int a[7];       // Массив адресов EEPROM. Хранятся адреса переменных.

  // Перечесление для удобного доступа к адресу переменной в EEPROM.
  // Сами адреса переменных хранятся в массиве a объявленном выше.  
  enum n_addr {    
  a_Recorded,

  a_ModeAuto,
  a_RLL,  
  a_Ts,
  a_D,
  a_RegulatorType,
  a_DELAY_Backlight
  };

// Функция служит для автоматического заполнения Массива адресов EEPROM.
void setupAddrEEPROM(){
  a[a_Recorded]=addr;             addr+=sizeof(Recorded); 
  a[a_ModeAuto]=addr;             addr+=sizeof(ModeAuto);
  a[a_RLL]=addr;                  addr+=sizeof(RLL); 
  a[a_Ts]=addr;                   addr+=sizeof(Ts);
  a[a_D]=addr;                    addr+=sizeof(D);
  a[a_RegulatorType]=addr;        addr+=sizeof(RegulatorType); 
  a[a_DELAY_Backlight]=addr;      addr+=sizeof(DELAY_Backlight); 

  // Выводит таблицу:
  //             / адрес в EEPROM         /       ИМЯ переменной             / Размер занимаемый переменной в байтах /
  Serial.println("");
  Serial.print(a[n_addr::a_Recorded]);        Serial.print(" Recorded ");         Serial.println(sizeof(Recorded));
  Serial.print(a[n_addr::a_ModeAuto]);        Serial.print(" ModeAuto ");         Serial.println(sizeof(ModeAuto));
  Serial.print(a[n_addr::a_RLL]);             Serial.print(" RLL ");              Serial.println(sizeof(RLL));
  Serial.print(a[n_addr::a_Ts]);              Serial.print(" Ts ");               Serial.println(sizeof(Ts));  
  Serial.print(a[n_addr::a_D]);               Serial.print(" D ");                Serial.println(sizeof(D)); 
  Serial.print(a[n_addr::a_RegulatorType]);   Serial.print(" RegulatorType ");    Serial.println(sizeof(RegulatorType));
  Serial.print(a[n_addr::a_DELAY_Backlight]); Serial.print(" DELAY_Backlight ");  Serial.println(sizeof(DELAY_Backlight));   
  Serial.println(addr);
  
} 

// Читаем все сохраненные настройки из EEPROM
void ReadEEPROM()
{
  EEPROM.begin(addr);
    EEPROM_readAnything(a[a_ModeAuto], ModeAuto);
    EEPROM_readAnything(a[a_RLL], RLL);
    EEPROM_readAnything(a[a_RegulatorType], RegulatorType); 
    EEPROM_readAnything(a[a_DELAY_Backlight], DELAY_Backlight); 
    EEPROM.get(a[a_Ts],  Ts);
    EEPROM.get(a[a_D],   D);
  EEPROM.end();
}

void setupEEPROM(){
  Serial.print("EEPROM Begin!");
  setupAddrEEPROM();

  EEPROM.begin(addr);
  EEPROM_readAnything(a[a_Recorded], Recorded); // Прочитаем из EEPROM состониие переменной Recorded
  
  // Если в переменной Recorded ненаходится слова true то запишем в EEPROM базовые настройки
  if (Recorded == false){
    Recorded=true;
    EEPROM_writeAnything(a[a_Recorded], Recorded);

    EEPROM_writeAnything(a[a_RegulatorType], RegulatorType);
    EEPROM_writeAnything(a[a_DELAY_Backlight], DELAY_Backlight);
    EEPROM_writeAnything(a[a_ModeAuto], ModeAuto);
    EEPROM_writeAnything(a[a_RLL], RLL);
    EEPROM.put(a[a_Ts],  Ts);
    EEPROM.put(a[a_D],   D);
  }
  EEPROM.end();
  
  ReadEEPROM();
  Serial.println("  Done!");   
}
