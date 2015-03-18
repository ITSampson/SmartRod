#include <SoftwareSerial.h>

SoftwareSerial BT(1, 0); 
// creates a "virtual" serial port/UART
// connect BT module TX to D1
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

void setup()  
{
   Serial.begin(9600);
  // set digital pin to control as an output
  pinMode(9, OUTPUT);
Serial.println("ALARM");
  // set the data rate for the SoftwareSerial port
  BT.begin(115200);
   digitalWrite(9, HIGH);

  // Send test message to other device

}

char a; // stores incoming character from other device

void loop() 
{
  Serial.println("ALARM");
  BT.println("ALARM");
delay(1000);
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a=(BT.read());
    if (a=='1')
    {
      digitalWrite(9, HIGH);
     // BT.println("LED on");
    }
    if (a=='2')
    {
      digitalWrite(9, LOW);
     // BT.println("LED off");
    }
    if (a=='?')
    {
    //  BT.println("Send '1' to turn LED on");
    //  BT.println("Send '2' to turn LED on");
    }   
    // you can add more "if" statements with other characters to add more commands
  }
}
