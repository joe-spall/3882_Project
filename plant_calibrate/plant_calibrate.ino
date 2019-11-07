#include <Servo.h>

Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
int servo0Pin = 9;
int servo1Pin = 10;
int servo2Pin = 11;

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
}
