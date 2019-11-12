#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop() {
	myservo.write(180);
	delay(15);                       // waits 15ms for the servo to reach the position
 }