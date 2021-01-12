#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git

// Справка по библиотеке https://wiki.iarduino.ru/page/Working_with_character_LCD_displays

  // GPIO занятые I2C
    // A4 SDA
    // A5 SCL
    
LiquidCrystal_I2C lcd(0x3F,16,2);  // устанавливаем адрес LCD 0x27 (или 0x3F) 16 символов и 2 строки
// Или воспользуйтес скетчем I2C_Skaner для определения адреса устройства

// Настройка экрана LCD16x2
void setupLCD16x2(){
 
  lcd.begin();     // Инициализируем LCD
  lcd.backlight(); // Включаем подсветку.
  
  lcd.setCursor(0,0);
  lcd.print("Thermostat");
  lcd.setCursor(0,1);
  lcd.print("Version V7    ");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("of 04/02/2019.");
  
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("From the");
  lcd.setCursor(0,1);
  lcd.print("Engineering Room");
  delay(2000); 

   
  lcd.clear();
}

// Главный экран LCD16x2
void MainScreen(){
  // Служит для обновления информации на LSD дисплее с заданной частотой (DELAY_LCD1)
  if (ms - msLCD1 > DELAY_LCD1){
    
  lcd.setCursor(0,0);
  lcd.print("Tin");
  lcd.print(TempIn1, 1);
  lcd.print(" ");

  lcd.setCursor(8,0);
  lcd.print("Tset");
  lcd.print(Ts, 1);
  lcd.print(" ");

  lcd.setCursor(0,1);
  lcd.print("Rout ");
    if (StateRelay1){lcd.print("ON ");}
    else            {lcd.print("OFF");}

  lcd.setCursor(10,1);
    if (ModeAuto)   {lcd.print("Auto  ");}
    else            {lcd.print("Manual");}
    
  msLCD1 = ms; // Время последнего вывода информации на LCD
  }//if (ms - msLCD1 > DELAY_LCD1)
}

// Вывод меню настроек на экран LCD16x2
void SetMenuScreen(String S){
  if (ms - msLCD1 > DELAY_LCD1){
    lcd.setCursor(1,0);
    lcd.print("  <Settings>  ");
  
    lcd.setCursor(1,1);
    lcd.print(S);
    
  msLCD1 = ms; // Время последнего вывода информации на LCD
  }//if (ms - msLCD1 > DELAY_LCD1)
}

// Справка!!!
// Полиморфизм. Функции с одинаковым именем (для удобства использования),
// но принемают разные аргументы. (Потому на такой синтаксис не ругается компилятор)

// Вывод меню настройки переменных типа float на экран LCD16x2
    // S   - название переменной
    // Val - переменная
    // Suf - суфикс. Пример: "С" Градус Цельсия
  void SettingsScreen(String S, float Val, String Suf){
    if (ms - msLCD1 > DELAY_LCD1){
      
      lcd.setCursor(1,0);
      lcd.print(S);
      lcd.setCursor(1,1);
      lcd.print(Val, 1);
      lcd.print(Suf);
  
      lcd.print(" +/-");
      lcd.print(Rank, 1);
      
    msLCD1 = ms; // Время последнего вывода информации на LCD
    }//if (ms - msLCD1 > DELAY_LCD1)
  }

// Вывод меню настройки переменных типа uint32_t на экран LCD16x2
    // S   - название переменной
    // Val - переменная
    // Suf - суфикс. Пример: "sec" Секунда
  void SettingsScreen(String S, uint32_t Val, String Suf){
    if (ms - msLCD1 > DELAY_LCD1){
      
      lcd.setCursor(1,0);
      lcd.print(S);
      lcd.setCursor(1,1);
      lcd.print(Val/1000);
      lcd.print(Suf);
  
    msLCD1 = ms; // Время последнего вывода информации на LCD
    }//if (ms - msLCD1 > DELAY_LCD1)
  }

// Вывод меню настройки переменных типа bool на экран LCD16x2
    // S     - название переменной
    // Val   - переменная
    // TRUE  - "Строка" если переменная Val=правда. Пример: "AUTO  "
    // FALSE - "Строка" если переменная Val=лож.    Пример: "MANUAL"
  void SettingsScreen(String S, bool Val, String TRUE, String FALSE){
    if (ms - msLCD1 > DELAY_LCD1){
      
      lcd.setCursor(1,0);
      lcd.print(S);
      lcd.setCursor(1,1);
        if (Val)   {lcd.print(TRUE);}
        else       {lcd.print(FALSE);}
        
    msLCD1 = ms; // Время последнего вывода информации на LCD
    }//if (ms - msLCD1 > DELAY_LCD1)
  }

// Вывод меню настройки переменных типа int на экран LCD16x2
    // при этом число хранящаяся в int это тип регулятора
    // Таких режимов может быть очень много.
    // S     - название переменной
    // Val   - переменная
  void SettingsScreen(String S, int Val){
    if (ms - msLCD1 > DELAY_LCD1){
      
      lcd.setCursor(1,0);
      lcd.print(S);
      lcd.setCursor(1,1);
      String Smame = RegulatorTypeName[Val];
      lcd.print(Smame);
      
    msLCD1 = ms; // Время последнего вывода информации на LCD
    }//if (ms - msLCD1 > DELAY_LCD1)
  }
