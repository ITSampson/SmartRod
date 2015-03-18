/*  
  APC magazine
  Arduino Masterclass - Project #20
  Wireless Light'n'Sound
  Darren Yates - 8 July 2014
  Based on code from ArduDroid.ino by Hazim Bitar
*/

#define START_CMD_CHAR '*'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define PIN_HIGH 3
#define PIN_LOW 2

#include <AltSoftSerial.h>
AltSoftSerial arduinoBT;

void setup() {
  
  arduinoBT.begin(9600);
}

void loop() {
  arduinoBT.flush();
  char btChar = ' ';
  int btCommand = 0;
  int btPin = 0;
  int btPinValue = 0;

  if (arduinoBT.available()) {
    btChar = arduinoBT.read();
    if (btChar == START_CMD_CHAR) {
      btCommand = arduinoBT.parseInt();
      btPin = arduinoBT.parseInt();
      btPinValue = arduinoBT.parseInt();
      
      if (btCommand == CMD_DIGITALWRITE) {
        pinMode (btPin, OUTPUT);
        digitalWrite(btPin, btPinValue-2);
      } 
    
      if (btCommand == CMD_ANALOGWRITE) analogWrite(btPin, btPinValue); 
    }
  }

}  
