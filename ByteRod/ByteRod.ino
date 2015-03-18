

#include <SoftwareSerial.h>



//Motion Detector Alarm - Written by ScottC on 2/08/2012

//Global Variables and constants
const int buttonPin = 8; // button Pin connected to Analog 0
const int buzzerPin = 7; // buzzer Pin connected to Analog 1


//Accelerometer Pins
const int x = A0; // GReen X pin connected to Analog 3
const int y = A1; // Yellow Y pin connected to Analog 4
const int z = A2; // Z pin connected to Analog 5

//Accelerometer Pins
const int xBase = A3; // X pin connected to Analog 3
const int yBase = A4; // Y pin connected to Analog 4
//const int tipz = A2; // Z pin connected to Analog 5

int xBaseVal;
int yBaseVal;
//Alarm LED
const int ledPin = 9; // LED connected to Digital 8



int tolerance = 100; // Sensitivity of the Alarm
boolean calibrated = false; // When accelerometer is calibrated - changes to true
boolean moveDetected = false; // When motion is detected - changes to true



//Accelerometer limits
int xMin; //Minimum x Value
int xMax; //Maximum x Value
int xVal; //Current x Value

int yMin; //Minimum y Value
int yMax; //Maximum y Value
int yVal; //Current y Value

int zMin; //Minimum z Value
int zMax; //Maximum z Value
int zVal; //Current z Value


// http://www.seeedstudio.com/depot/bluetooth-shield-p-866.html
#define RxD 0
#define TxD 1

SoftwareSerial bluetooth(RxD, TxD);

int counter = 0;




void setup() {

  Serial.begin(9600);
  setupBluetooth();
  Serial.println("\nBluetooth Counter\n");
  //Begin Serial communication


  //Initilise LED Pin
  pinMode(ledPin, OUTPUT);

}



void loop() {
  // If the button is pressed, initialise and recalibrate the Accelerometer limits.
  if (digitalRead(buttonPin) == HIGH) { //(analogRead(buttonPin)>500){
    calibrateAccel();
  }

  // Once the accelerometer is calibrated - check for movement
  if (calibrated) {
    if (checkMotion()) {
      moveDetected = true;
    }
  }

  // If motion is detected - sound the alarm !
  if (moveDetected) {
    Serial.println("ALARM");
    ALARM();
    delay(1000);
  }

}





//This is the function used to sound the buzzer
void buzz(int reps, int rate, int pitch) {
  for (int i = 0; i < reps; i++) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, pitch, rate);
    digitalWrite(ledPin, LOW);
    delay(rate);
  }
}




// Function used to calibrate the Accelerometer
void calibrateAccel() {
  // reset alarm
  Serial.println("--CALIBRATING--");
  moveDetected = false;

  //initialise x,y,z variables
  xVal = analogRead(x);
  xMin = xVal;
  xMax = xVal;

  yVal = analogRead(y);
  yMin = yVal;
  yMax = yVal;

  zVal = analogRead(z);
  zMin = zVal;
  zMax = zVal;

  xBaseVal = analogRead(xBase);
  yBaseVal = analogRead(yBase);

  // Calibration sequence initialisation sound - 3 seconds before calibration begins
  buzz(3, 300, 400);

  //calibrate the Accelerometer (should take about 0.5 seconds)
  for (int i = 0; i < 600; i++) {
    // Calibrate X Values
    xVal = analogRead(x);
    if (xVal > xMax) {
      xMax = xVal;
    } else if (xVal < xMin) {
      xMin = xVal;
    }

    // Calibrate Y Values
    yVal = analogRead(y);
    if (yVal > yMax) {
      yMax = yVal;
    } else if (yVal < yMin) {
      yMin = yVal;
    }

    // Calibrate Z Values
    zVal = analogRead(z);
    if (zVal > zMax) {
      zMax = zVal;
    } else if (zVal < zMin) {
      zMin = zVal;
    }

    //Delay 10msec between readings
    delay(10);
  }

  //End of calibration sequence sound. ARMED.
  buzz(3, 40, 200);
  printValues(); //Only useful when connected to computer- using serial monitor.
  calibrated = true;

}



//Function used to detect motion. Tolerance variable adjusts the sensitivity of movement detected.
boolean checkMotion() {
  boolean tempB = false;
  xVal = analogRead(x);
  yVal = analogRead(y);
  zVal = analogRead(z);

//  if (xVal > (xMax + tolerance) || xVal < (xMin - tolerance)) {
//    tempB = true;
//    Serial.print("X Failed = ");
//    Serial.println(xVal);
//  }
//
//  if (yVal > (yMax + tolerance) || yVal < (yMin - tolerance)) {
//    tempB = true;
//    Serial.print("Y Failed = ");
//    Serial.println(yVal);
//  }

  if (zVal > (zMax + tolerance) || zVal < (zMin - tolerance)) {
    tempB = true;
    Serial.print("Z Failed = ");
    Serial.println(zVal);
  }

  return tempB;
}





// Prints the Sensor limits identified during Accelerometer calibration.
// Prints to the Serial monitor.
void printValues() {
//
//  Serial.print("xBase=");
//  Serial.print(xBaseVal);
//  Serial.print(", yBase=");
//  Serial.print(yBaseVal);
//  Serial.println();
//
//  Serial.print("x=");
//  Serial.print(xVal);
//  Serial.print(", y=");
//  Serial.print(yVal);
//  Serial.println();
//
//  Serial.print("xMin=");
//  Serial.print(xMin);
//  Serial.print(", xMax=");
//  Serial.print(xMax);
//  Serial.println();
//
//  Serial.print("yMin=");
//  Serial.print(yMin);
//  Serial.print(", yMax=");
//  Serial.print(yMax);
//  Serial.println();

  Serial.print("zMin=");
  Serial.print(zMin);
  Serial.print(", zMax=");
  Serial.print(zMax);
  Serial.println();

  Serial.println("------------------------");
  Serial.println(zVal);

 // bluetooth.println('dd='& char(xVal) + 'y=' +  char(yVal) + 'z=' +  char(zVal));
}




//Function used to make the alarm sound, and blink the LED.
void ALARM() {

  //don't check for movement until recalibrated again
  calibrated = false;

  // sound the alarm and blink LED

  buzz(4, 200, 800);

  moveDetected = false;
}


// Seeed Studio Bluetooth Shield
void setupBluetooth()
{
  bluetooth.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  bluetooth.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  bluetooth.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  bluetooth.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  bluetooth.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  bluetooth.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
  //  Serial.println("The slave bluetooth is inquirable!");  // discoverable??
  delay(2000); // This delay is required.
  bluetooth.flush();
}

