#include <EEPROM.h>    
#include "EEPROMAnything.h" // http://playground.arduino.cc/Code/EEPROMWriteAnything
     
bool Recorded = false;

void setup() {
  
  EEPROM_writeAnything(0, Recorded);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
