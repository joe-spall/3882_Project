#include <Servo.h>

 #define CAL_MAX 10
 
/*
        _______
      /    3    \
    /             \
   | 2           0 |
   |               |
    \             /
      \    1     /
       --------
Light sensor mounting
*/

int photocell0Pin = A0;     // the cell and 1K pulldown are connected to a0
int photocellReading0;     // the analog reading from the sensor divider
int photocellBase0;
int photocellDelta0;

int photocell1Pin = A1;     // the cell and 1K pulldown are connected to a1
int photocellReading1;     // the analog reading from the sensor divider
int photocellBase1;
int photocellDelta1;

int photocell2Pin = A2;     // the cell and 1K pulldown are connected to a2
int photocellReading2;     // the analog reading from the sensor divider
int photocellBase2;
int photocellDelta2;

int photocell3Pin = A3;     // the cell and 1K pulldown are connected to a3
int photocellReading3;     // the analog reading from the sensor divider
int photocellBase3;
int photocellDelta3;


bool calibrated;
int calibrateCounter;

/*
        _______
      /         \
    /             \
   | 2           0 |
   |               |
    \             /
      \    1     /
       --------
Servo mounting
*/

Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
int servo0Pin = 10;
int servo1Pin = 9;
int servo2Pin = 11;
// twelve servo objects can be created on most boards

int servo0Pos;    // variable to store the servo position
int servo1Pos;    // variable to store the servo position
int servo2Pos;    // variable to store the servo position

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);  
  servo0.attach(servo0Pin);  // attaches the servo on pin 9 to the servo object
  servo1.attach(servo1Pin);  // attaches the servo on pin 9 to the servo object
  servo2.attach(servo2Pin);  // attaches the servo on pin 9 to the servo object


  calibrated = false;
  calibrateCounter = 0;

  servo0Pos = 0;
  servo1Pos = 0;
  servo2Pos = 0;

  photocellBase0 = 0;
  photocellBase1 = 0;
  photocellBase2 = 0;
  photocellBase3 = 0;

  photocellDelta0 = 0;
  photocellDelta1 = 0;
  photocellDelta2 = 0;
  photocellDelta3 = 0;
}
 
void loop(void) {
  if(!calibrated){
    calibrateBaseline();
  }
  photocellReading0 = analogRead(photocell0Pin);
  photocellReading1 = analogRead(photocell1Pin);
  photocellReading2 = analogRead(photocell2Pin);
  photocellReading3 = analogRead(photocell3Pin);

  photocellDelta0 = photocellReading0 - photocellBase0;
  photocellDelta1 = photocellReading1 - photocellBase1;
  photocellDelta2 = photocellReading2 - photocellBase2;
  photocellDelta3 = photocellReading3 - photocellBase3;

  // Photocell 3 greater than Photocell 1
  if(photocellDelta3 - photocellDelta1 > 0 && servo1Pos < 180){
    servo1Pos += 1
  }

  // Photocell 1 greater than Photocell 3
  if(photocellDelta1 - photocellDelta3 > 0 && servo1Pos > 0){
    servo1Pos -= 1
  }
  
  servo1.write(servo1Pos);
 
  delay(100);
}

void calibrateBaseline(){
  while(calibrateCounter < CAL_MAX){
      photocellBase0 += analogRead(photocell0Pin);
      photocellBase1 += analogRead(photocell1Pin);
      photocellBase2 += analogRead(photocell2Pin);
      photocellBase3 += analogRead(photocell3Pin);
      calibrateCounter++;
      delay(1);
  }
  photocellBase0 /= CAL_MAX;
  photocellBase1 /= CAL_MAX;
  photocellBase2 /= CAL_MAX;
  photocellBase3 /= CAL_MAX;
  calibrated = true;
}
