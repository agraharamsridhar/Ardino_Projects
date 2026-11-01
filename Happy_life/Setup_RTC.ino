#include <Arduino.h>
#include <avr/pgmspace.h>
#include<DS3231.h>
#include<Wire.h>

/* Creating rtv object*/

DS3231 myRTC;

bool h12;
bool PM_time;
bool century;

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
    Wire.begin();

  while (!Serial.available()) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (Serial.available()) 
  {
    char inputChar;
    inputChar = Serial.read();
    if(inputChar == 'C')
    {
    
    myRTC.setClockMode(false);

      myRTC.setYear(26);
      myRTC.setMonth(11);
      myRTC.setDate(1);
      myRTC.setDoW(7);
      myRTC.setHour(14);
      myRTC.setMinute(11);
      myRTC.setSecond(30); 
    }
    else
    {
      Serial.print("Not given C");
    }
  }  

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(2000+myRTC.getYear(),DEC);
  Serial.print("-");
  Serial.print(myRTC.getMonth(century),DEC);
  Serial.print("-");
  Serial.print(myRTC.getDate(), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getHour(h12, PM_time), DEC); //24-hr
  Serial.print(":");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(":");
        Serial.println(myRTC.getSecond(), DEC);
  delay(5000);

}
