#include<EEPROM.h>
#include <Arduino.h>
#include<Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  int i;
  for(i=0;i<EEPROM.length();i++)
  {
    EEPROM.write(i, 0);
  }

  EEPROM.put(100, 16071);
  EEPROM.put(200,2295);
}

void loop() {
  // put your main code here, to run repeatedly
}
