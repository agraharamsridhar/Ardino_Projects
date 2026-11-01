#include<EEPROM.h>
#include <Arduino.h>
#include <TM1637TinyDisplay.h>
#include <avr/pgmspace.h>
#include<DS3231.h>
#include<Wire.h>

DS3231 myRTC;

byte year;
byte month;
byte date;
byte day;
int hour;
int min;
byte sec;

bool h12;
bool PM_time;
bool century;

#define INTERRUPT_PIN 2
// Volatile flag for ISR-to-loop communication
volatile bool alarmTriggered = false;

// Define Digital Pins
#define CLK 4
#define DIO 5

// Initialize TM1637TinyDisplay
TM1637TinyDisplay display(CLK, DIO);

typedef struct my_left_over
{
  int days;
  int weeks;
}my_left_over;

my_left_over current;

// Interrupt Service Routine (ISR)
void alarmISR() {
  alarmTriggered = true;
}


void setup() {

  Wire.begin();
  Serial.begin(9600);
  display.begin();
  display.setBrightness(7);

  EEPROM.get(100,current.days);
  EEPROM.get(200,current.weeks);

/* Interrupt settings*/
pinMode(INTERRUPT_PIN, INPUT_PULLUP);
myRTC.checkIfAlarm(1);
myRTC.checkIfAlarm(2);

byte currentDay = myRTC.getDate();
myRTC.setA1Time(currentDay, 0, 0, 0, 0b00010000, false, false, false);

myRTC.turnOnAlarm(1);

attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), alarmISR, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  /* Display of current time for 2 seconds*/
  hour = myRTC.getHour(h12,PM_time);
  min = myRTC.getMinute();
  int timeout = hour*100 + min;
  display.showNumberDec(timeout, 0b01000000, true);
 // display.showString(to_display);
  delay(2000);
  /*ENd of Dislay of current time code*/

  /* Show Date*/
    day = myRTC.getDate();
    month = myRTC.getMonth(century);
    display.showNumber(day*100+month);
    delay(2000);
  /* Display no.of days left over */
    char buffer[10];
    ltoa(current.days, buffer, 10);
 //   display.showNumber(current.days);
    display.showString(buffer);
    delay(2000);
  /* End of Display of no.of days left over*/

  /* Display of no.of weeks leftover*/
    display.showNumber(current.weeks);
    delay(2000);
  /* End of Display of no.of weeks leftover*/


  delay(2000);



/* change of Day*/

  if(alarmTriggered)
  {
    --current.days;
    EEPROM.put(100, current.days);

    if(myRTC.getDoW() == 1)
    {
      --current.weeks;
      EEPROM.put(200,current.weeks);
    }
    alarmTriggered = false;
    myRTC.checkIfAlarm(1);
  }

}
