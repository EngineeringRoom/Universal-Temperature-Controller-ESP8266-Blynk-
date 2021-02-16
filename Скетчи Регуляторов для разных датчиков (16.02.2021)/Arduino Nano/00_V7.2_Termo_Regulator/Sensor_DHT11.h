// Библиотека Adafruit Unified Sensor Driver // https://github.com/adafruit/Adafruit_Sensor.git
               
#include "DHT.h" // https://github.com/adafruit/DHT-sensor-library.git

#define GPIO_DHT1 11     // GPIO датчика DHT11

// Раскоментируйте тот тип датчика который используете!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Подключите контакт 1 (слева) датчика к + 5V
// ПРИМЕЧАНИЕ. Если вы используете плату с 3,3 В логикой, например, Arduino Due connect pin 1
// до 3,3 В вместо 5 В!
// Подключите контакт 2 датчика к вашему DHTPIN
// Подключите контакт 4 (справа) датчика к заземлению
// Подключаем резистор 10 кОм с контакта 2 (данные) к контакту 1 (питание) датчика

// Инициализация датчика DHT.
// Обратите внимание, что более старые версии этой библиотеки принимали необязательный третий параметр для
// настроить время для более быстрых процессоров. Этот параметр больше не нужен
// поскольку текущий алгоритм чтения DHT настраивается для работы на более быстрых процессорах.
DHT dht(GPIO_DHT1, DHTTYPE);

void setupSensor() {
  Serial.print("DHT begin!");

// Подключаем датчик температуры
  dht.begin();
  
  Serial.println("  Done!");  
}

void loopTempIn1(float &TempIn1) {
  // По умолчанию тут стоит delay(2000); Но нам это не подходит
  // заменяем на работу с millis();
  if (timer(msTempIn1, DELAY_TempIn1)){
    static int countError=0;
     
    // Чтение температуры или влажности занимает около 250 миллисекунд!
    // Показания датчика также могут быть «старыми» до 2 секунд (это очень медленный датчик)

    // Чтение температуры в градусах Цельсия (по умолчанию)
    float tDHT1 = dht.readTemperature();
  
    // Проверка, удалось ли выполнить чтение, и завершить работу если не удолось(чтобы повторить попытку).
    if (isnan(TempIn1)) {
      Serial.println("Failed to read from DHT sensor!");
      countError++;
      if (countError==5){Error=true;}
      return;
    }

    countError=0;
    Serial.print("Temperature: ");
    Serial.print(tDHT1);
    Serial.println(" *C ");

    TempIn1=tDHT1; 
  }
}
