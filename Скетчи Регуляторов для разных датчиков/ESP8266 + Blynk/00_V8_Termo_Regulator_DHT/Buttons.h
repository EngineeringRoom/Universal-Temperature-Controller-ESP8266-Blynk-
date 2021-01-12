#include "OneButton.h" // https://github.com/mathertel/OneButton.git

// true значит что кнопка подтянута к плюсу
// Конструктор класса OneButton
OneButton Select(GPIO_B_Select, true);
OneButton UP    (GPIO_B_UP,     true);
OneButton DOWN  (GPIO_B_DOWN,   true);

bool sSelect=false; // Переменная для хранения нажатия кнопки Select
bool sUP=false;     // Переменная для хранения нажатия кнопки UP
bool sDOWN=false;   // Переменная для хранения нажатия кнопки DOWN

bool slpUP=false;     // Переменная для хранения нажатия кнопки UP (Long Press)
bool slpDOWN=false;   // Переменная для хранения нажатия кнопки DOWN (Long Press)

int m=0;            // Используется для навигации по Меню

// Если долго не нажимали не одну кнопку, то выключим подсветку экрана
// Если долго не нажимали не одну кнопку, то заблокируем их
void checkButtonLock(){
  if (ms - msBacklight > DELAY_Backlight && DELAY_Backlight!=0){ // Если долго не нажимали не одну кнопку, то выключим подсветку экрана
    lcd.noBacklight();
  }
  if (ms - msBL > DELAY_ButtonLock && Buttonlock==false){ // Если долго не нажимали не одну кнопку, то заблокируем их
    m=0;
    lcd.clear();
    Buttonlock=true; //заблокировать кнопки
    Serial.println("Button lock ON");
  }
}

// Снять болокировку кнопок долгим удержанием кнопки Select
void SelectButtonlock() {
  lcd.backlight();  msBacklight=ms; // Включение посдветки
  
  Serial.println("Button lock OFF");
  Buttonlock=false;
  msBL=ms;        // Время последнего нажатия кнопки
} // SelectButtonlock


void Select_Click() {
  lcd.backlight();  msBacklight=ms; // Включение посдветки
  
  if (!Buttonlock){   // Если кнопки разблокированны
      Serial.print("Select_Click.");
      sSelect=true;
      msBL=ms; // Время последнего нажатия кнопки
  }
}// Select_Click

void UP_Click() {
  lcd.backlight();  msBacklight=ms;
  
  if (!Buttonlock){   // Если кнопки разблокированны
      Serial.println("UP_Click.");
      sUP=true;
      msBL=ms; // Время последнего нажатия кнопки
  }
}// UP_Click

void DOWN_Click() {
  lcd.backlight();  msBacklight=ms; // Включение посдветки
  
  if (!Buttonlock){   // Если кнопки разблокированны
      Serial.println("DOWN_Click.");
      sDOWN=true;
      msBL=ms; // Время последнего нажатия кнопки
  }
}// DOWN_Click

// Выбор порядка изменения переменных
void RankDirection(bool Direction){
  static int RankIndex=0;
  if (Direction) {RankIndex++; if (RankIndex > 2) {RankIndex=2;}}
  else           {RankIndex--; if (RankIndex < 0) {RankIndex=0;}}
  
  switch(RankIndex){
    case 0:
      Rank=0.1;
    break;
    case 1:
      Rank=1.0;
    break;
    case 2:
      Rank=10.0;
    break;
  }
}

void RankUP(){
  lcd.backlight();  msBacklight=ms; // Включение посдветки
    
  if (!Buttonlock){   // Если кнопки разблокированны
      Serial.println("LongPress UP.");
      slpUP=true;
      msBL=ms; // Время последнего нажатия кнопки
  }  
}

void RankDOWN(){
  lcd.backlight();  msBacklight=ms; // Включение посдветки
    
  if (!Buttonlock){   // Если кнопки разблокированны
      Serial.println("LongPress DOWN.");
      slpDOWN=true;
      msBL=ms; // Время последнего нажатия кнопки
  }  
}

// Это програмный ресет, который начинает код с 0
void(* resetFunc) (void) = 0; // объявляем функцию reset


// Меню
void Menu(){

  switch(m){
    case 0: 
      MainScreen();
      if (sSelect){m=1; lcd.clear();}
      if (!ModeAuto){
        if (sUP)    {StateRelay1 = true;}
        if (sDOWN)  {StateRelay1 = false;}        
      }
    break;
    //---<SETTINGS>
        case 1:
          SetMenuScreen("Exit            ");
          if (sSelect){m=0; lcd.clear();}
          if (sDOWN)  {m++;}
        break;
            
        case 2:
          SetMenuScreen("Temp setting    ");
          if (sSelect){m=21; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 21:
                        if (sUP)    {Ts+=Rank;}
                        if (sDOWN)  {Ts-=Rank;}
                        if (slpUP)    {RankDirection(HIGH);}
                        if (slpDOWN)  {RankDirection(LOW);}
                        SettingsScreen("Temp setting   ", Ts, "C  ");
                        if (sSelect){m=2; EEPROM.begin(addr); EEPROM.put(a[a_Ts],  Ts); EEPROM.end(); Blynk.virtualWrite(VPIN_Ts, Ts); lcd.clear();}
                      break;    
    
        case 3:
          SetMenuScreen("Hysteresis      ");
          if (sSelect){m=31; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 31:
                        if (sUP)    {D+=Rank;}
                        if (sDOWN)  {D-=Rank;}
                        if (slpUP)    {RankDirection(HIGH);}
                        if (slpDOWN)  {RankDirection(LOW);}
                        SettingsScreen("Hysteresis     ", D, "C  ");
                        if (sSelect){m=3; EEPROM.begin(addr); EEPROM.put(a[a_D],  D); EEPROM.end(); lcd.clear();}
                      break;
                      
        case 4:
          SetMenuScreen("Mode            ");    
          if (sSelect){m=41; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 41:
                        if (sUP)    {ModeAuto=true;}
                        if (sDOWN)  {ModeAuto=false;}
                        SettingsScreen("Mode           ", ModeAuto, "Auto  ", "Manual");
                        if (sSelect){m=4; EEPROM.begin(addr); EEPROM_writeAnything(a[a_ModeAuto], ModeAuto); EEPROM.end();  lcd.clear();}
                      break;
                      
        case 5:
          SetMenuScreen("Regulator Type  ");    
          if (sSelect){m=51; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 51:
                        if (sUP)    {RegulatorTypeSwitch(LOW);}
                        if (sDOWN)  {RegulatorTypeSwitch(HIGH);}
                        SettingsScreen("Regulator Type ", RegulatorType);
                        if (sSelect){m=5; EEPROM.begin(addr); EEPROM_writeAnything(a[a_RegulatorType], RegulatorType); EEPROM.end(); lcd.clear();}
                      break;


        case 6:         
          SetMenuScreen("Delay Light     ");
          if (sSelect){m=61; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 61:
                        if (sUP)    {DELAY_Backlight+=10000;}
                        if (sDOWN)  {if (DELAY_Backlight!=0){DELAY_Backlight-=10000;} }
                        SettingsScreen("Delay Light    ", DELAY_Backlight, "sec ");
                        if (sSelect){m=6; EEPROM.begin(addr); EEPROM.put(a[a_DELAY_Backlight],  DELAY_Backlight); EEPROM.end(); lcd.clear();}
                      break;
    
        case 7:
          SetMenuScreen("RelayLogicLevel "); 
                            
          if (sSelect){m=71; lcd.clear();}
          if (sUP)    {m--;}
          if (sDOWN)  {m++;}
        break;
        //------------
                      case 71:
                        if (sUP)    {RLL=HIGH;}
                        if (sDOWN)  {RLL=LOW;}
                        SettingsScreen("RelayLogicLevel", RLL, "HIGH", "LOW ");
                        if (sSelect){m=7; EEPROM.begin(addr); EEPROM_writeAnything(a[a_RLL], RLL); EEPROM.end(); lcd.clear();}
                      break;
                                        
        case 8:
          SetMenuScreen("Reset Factory   ");    
          if (sSelect){m=81; lcd.clear();}
          if (sUP)    {m--;}
        break;
        //------------
                      case 81:
                        if (sUP)    {Recorded=false;}
                        if (sDOWN)  {Recorded=true;}
                        SettingsScreen("Reset Factory  ", !Recorded, "Yes", "No ");
                        if (sSelect){m=8; EEPROM.begin(addr); EEPROM_writeAnything(a[a_Recorded], Recorded); EEPROM.end(); lcd.clear();
                          Serial.println("Overwriting factory settings in EEPROM");
                          delay(100);
                          resetFunc(); //вызываем reset
                        }
                      break;                          
  }//switch(m)
}//Menu()

// Настройка Кнопок
void setupButtons() {

// Подключение функций кнопок
  Select.attachClick(Select_Click);
  Select.attachLongPressStart(SelectButtonlock);
  
  UP.attachClick(UP_Click);
  UP.attachLongPressStart(RankUP);
  
  DOWN.attachClick(DOWN_Click);
  DOWN.attachLongPressStart(RankDOWN);
  

// Подключение функций кнопки (Примеры)
//  button1.attachClick(click1);
//  button1.attachDoubleClick(doubleclick1);
//  button1.attachLongPressStart(longPressStart1);
//  button1.attachLongPressStop(longPressStop1);
//  button1.attachDuringLongPress(longPress1);

} // setup

// Цикл в котором происходит опрос кнопок
void loopButtons() {
  // следим за кнопками:
  Select.tick();
  UP.tick();
  DOWN.tick();  
}

// Здесь обнуляются флаги который могли быть подняты при нажатии кнопки в предидущем цикле
void ButtonsLOW(){
  sSelect=false;
  sUP=false;
  sDOWN=false;
  
  slpUP=false;
  slpDOWN=false;
}
