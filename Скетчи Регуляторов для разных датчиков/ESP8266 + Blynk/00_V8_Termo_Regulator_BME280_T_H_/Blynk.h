/* Закомментируйте это, чтобы отключить BLYNK_LOG и сэкономить место */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "Connect.h" // Подключаем вкладку Connect.h

BlynkTimer timer; // Объявляем Таймер

WidgetLED led1(VPIN_StateRelay1); // Объявляем виджет LED

BLYNK_WRITE(VPIN_Ts) {
  if (Error==false){
    Ts = param.asFloat(); // Получаем значение в виде Float из приложения
    // Запись нового значения Уставки в EEPROM
    EEPROM.begin(addr);
      EEPROM.put(a[a_Ts],  Ts);
    EEPROM.end();
  }
}

// При подключении к Blynk отправим значения на сервер
BLYNK_CONNECTED(){
  Blynk.virtualWrite(VPIN_TempIn1, TempIn1);        // Температура от датчика
  Blynk.virtualWrite(VPIN_HumidIn1, HumidIn1);      // Влажность от датчика
  Blynk.virtualWrite(VPIN_Ts, Ts);
  if (StateRelay1) {led1.on();} else {led1.off();}
}

// Отправляем данные в приложение
void SendBlynk(){
  if (Error==false){
    Blynk.virtualWrite(VPIN_TempIn1, TempIn1);        // Температура от датчика
    Blynk.virtualWrite(VPIN_HumidIn1, HumidIn1);      // Влажность от датчика
    if (StateRelay1) {led1.on();} else {led1.off();}  // Состояние Реле
  }
}


void setupBlynk(){
// Вызываем функцию подключения к Blynk
  reconnectBlynk();

// Настраеваем таймеры  
  timer.setInterval(1000, SendBlynk);
  timer.setInterval(10000, reconnectBlynk);
}

void loopBlynk(){
  if (Blynk.connected()){ Blynk.run();} 
  timer.run();
}
