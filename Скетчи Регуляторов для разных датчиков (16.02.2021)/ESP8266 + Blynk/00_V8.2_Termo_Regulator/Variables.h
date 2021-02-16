// Первое ли это подключение к Серверу
  bool isFestConnection=true;
  
// ID для таймеров Blynk
  int IDt_reconnectBlynk; // ID таймера для перезагрузки

/////////////////////////////////////////
//   База переменных для подключения   //

// Логин и пароль от WiFi
String _ssid     = "ssidwifw"; // Для хранения SSID
String _password = "12345678"; // Для хранения пароля сети

// Ключ Blynk
String _authB = "11112222333344445555666677778888";    // AUTH токен Blynk
String _serverB = "blynk-cloud.com";                   // Сервер Blynk "blynk-cloud.com"
String _portB = "8080";                                // Порт сервера Blynk "8080"

////////////////////////////////////
//        База виртуальных GPIO Blynk

#define VPIN_TempIn1      V0
#define VPIN_Ts           V1
#define VPIN_StateRelay1  V2

////////////////////////////////////
//        База GPIO

  // GPIO занятые I2C
  //  Плата ESP-12E подключаем SCL - D1(GPIO5) // SDA - D2(GPIO4)
  //  Плата Arduino UNO (NANO) SCL - А5 // SDA - А4

  // GPIO датчика температуры Объявлен во вкладке Sensor.h)

  #define GPIO_B_Select  D5   // Кнопка Выбор
  #define GPIO_B_UP      D6   // Кнопка Вверх
  #define GPIO_B_DOWN    D7   // Кнопка Вниз

  #define GPIO_Relay1    D3   // Реле 1 (Выход терморегулятора)  
    
////////////////////////////////////
//        База переменных
  // Флаг ошибки. Если true то ошибка, если false то все хорошо
    bool Error=false;
  
  // Данные от датчика температуры
    float TempIn1;

  // Переменные для терморегулятора
    float Ts = 20.0;            // Уставка терморегулятора                            (Factory Settings)
    float D =  0.5;             // Дельта (Гистерезес) терморегулятора                (Factory Settings)
    float Rank=0.1;             // Ранг(шаг) изменения переменных Ts и D              
        
    bool StateRelay1 = false;   // Состояние выхода Реле 1 (Выход терморегулятора)

    bool ModeAuto = false;      // Режим рулятора (Автоматический/Ручной)(true/false) (Factory Settings)
    bool RLL = HIGH;            // Relay Logic Level (Уровень Логики Реле)            (Factory Settings)

  
    bool Buttonlock=true;       // Блокировка кнопок
    


  // Переменные для таймера на millis();
    uint32_t ms;            // Хранит время с начала работы МК

    // Хранят время с последнего события
    uint32_t msTempIn1;     // Служит для опроса датчика температуры с заданным интевалом
    uint32_t msLCD1;        // Служит для обновления информации на LSD дисплее с заданной частотой
    uint32_t msBL;          // Служит для блокировки кнопок по истечению заданного промежутка времени
    uint32_t msBacklight;   // Служит для отключения подсветки экрана по истечению заданного промежутка времени

    const uint32_t DELAY_TempIn1=2000;  // Частота опроса датчика температуры
    const uint32_t DELAY_LCD1=200;      // Частота обновления информации на LCD экране
    
    const uint32_t DELAY_ButtonLock=30000; // время блокировки кнопок при бездействии
    uint32_t DELAY_Backlight=30000UL; // время отключения подсветки экрана при бездействии (Factory Settings)
    
