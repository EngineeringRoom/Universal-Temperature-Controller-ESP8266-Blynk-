// Перечесление Типов регулятора
  enum enumRegulatorType {
    HEATER,
    COOLER
  };

// Массив с именами Типов регулятора
  String RegulatorTypeName[2]={
    "HEATER",
    "COOLER"
  };

  int RegulatorType=HEATER; // Тип регулятора

// Функция переключатель Типов регулятора
void RegulatorTypeSwitch(bool Direction){
  if (Direction) {RegulatorType++; if (RegulatorType > COOLER) {RegulatorType=COOLER;}}
  else           {RegulatorType--; if (RegulatorType < HEATER) {RegulatorType=HEATER;}}
  
  switch(RegulatorType){
    case 0:
      RegulatorType=HEATER;
    break;
    case 1:
      RegulatorType=COOLER;
    break;
  }
}
  
void Regulator(int RegulatorType, // Тип регулятора (HEATER, COOLER)
               bool Mode,         // Режим рулятора (Автоматический/Ручной)(HIGH/LOW)
               float TempIn,      // Температура от датчика температуры
               float TempSet,     // Уставка температуры
               float Delta,       // Дельта (Гистерезис)
               bool &State,       // Состояние выхода (Включен/Выключен)(HIGH/LOW)
               int GPIO,          // GPIO микроконтроллера к которуму подключено Реле
               bool RLL           // Уровень Логики Реле. Каким сигналом управляется (HIGH/LOW)
               ){
                
  if (Mode){ // Если true то включен автоматический режим
    if(RegulatorType==HEATER){        // Если Тип регулятора Нагреватель
      if (TempIn < TempSet-Delta) {State=HIGH;}
      if (TempIn > TempSet+Delta) {State=LOW;}
    }
    else if(RegulatorType==COOLER){   // Если Тип регулятора Охладитель
      if (TempIn > TempSet+Delta) {State=HIGH;}
      if (TempIn < TempSet-Delta) {State=LOW;}
    }
  }
  // Уровень Логики Реле. Каким сигналом управляется (HIGH/LOW)
  if (RLL){digitalWrite(GPIO,  State);}
  else    {digitalWrite(GPIO, !State);}
  
}//Regulator
