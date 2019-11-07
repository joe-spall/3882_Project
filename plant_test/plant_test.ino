#include <Servo.h>

 #define CAL_MAX 10
 
int photocell0Pin = A0;     // the cell and 10K pulldown are connected to a0
int photocellReading0;     // the analog reading from the sensor divider
int photocellBase0;
int photocellDelta0;

int photocell1Pin = A1;     // the cell and 10K pulldown are connected to a0
int photocellReading1;     // the analog reading from the sensor divider
int photocellBase1;
int photocellDelta1;

bool calibrated;
int calibrateCounter;

Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
int servo0Pin = 9;
int servo1Pin = 10;
// twelve servo objects can be created on most boards

int servo0Pos = 0;    // variable to store the servo position
int servo1Pos = 0;    // variable to store the servo position

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);  
  servo0.attach(servo0Pin);  // attaches the servo on pin 9 to the servo object
  servo1.attach(servo1Pin);  // attaches the servo on pin 9 to the servo object

  calibrated = false;
  calibrateCounter = 0;
  photocellBase0 = 0;
  photocellDelta0 = 0;
  photocellBase1 = 0;
  photocellDelta1 = 0;

}
 
void loop(void) {
  if(!calibrated){
    calibrateBaseline();
  }
  photocellReading0 = analogRead(photocell0Pin);
  photocellDelta0 = photocellReading0 - photocellBase0;
  photocellReading1 = analogRead(photocell1Pin);
  photocellDelta1 = photocellReading1 - photocellBase1;
  servo0Pos = map(photocellReading0, 0, 1023, 0, 180);
  servo1Pos = map(photocellReading1, 0, 1023, 0, 180);
  Serial.print(photocellReading0);     // the raw analog reading
  Serial.print(" ");
  Serial.print(photocellDelta0);     // the delta reading
  Serial.print(" ");
  Serial.println(servo0Pos);     // the delta reading
  
  servo0.write(servo0Pos);
  servo1.write(servo1Pos);
 
  delay(100);
}

void calibrateBaseline(){
  while(calibrateCounter < CAL_MAX){
      photocellBase0 += analogRead(photocell0Pin);
      photocellBase1 += analogRead(photocell1Pin);
      calibrateCounter++;
      delay(1);
  }
  photocellBase0 /= CAL_MAX;
  photocellBase1 /= CAL_MAX;
  calibrated = true;
}
