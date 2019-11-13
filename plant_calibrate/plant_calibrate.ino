#include <Servo.h>

Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
int servo0Pin = 10;
int servo1Pin = 9;
int servo2Pin = 11;
int pRes0Pin = A0;
int pRes1Pin = A1;
int pRes2Pin = A2;
int pRes3Pin = A3;
int pRes0Reading;
int pRes1Reading;
int pRes2Reading;
int pRes3Reading;

void setup() {
  // put your setup code here, to run once:
  servo0.attach(servo0Pin);  // attaches the servo on pin 9 to the servo object
  servo1.attach(servo1Pin);  // attaches the servo on pin 9 to the servo object
  servo2.attach(servo2Pin);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  delay(10);

  pRes0Reading = analogRead(pRes0Pin);
  pRes1Reading = analogRead(pRes1Pin);
  pRes2Reading = analogRead(pRes2Pin);
  pRes3Reading = analogRead(pRes3Pin);

  if(pRes0Reading == 0 || pRes0Reading == 1023){
    Serial.println("photoresistor 0 is fucked");
  }

  if(pRes1Reading == 0 || pRes1Reading == 1023){
    Serial.println("photoresistor 1 is fucked");
  }

  if(pRes2Reading == 0 || pRes2Reading == 1023){
    Serial.println("photoresistor 2 is fucked");
  }

  if(pRes3Reading == 0 || pRes3Reading == 1023){
    Serial.println("photoresistor 3 is fucked");
  }
}
