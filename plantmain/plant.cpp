
#include "plant.h"

#include "Arduino.h"

plant::plant(){

}


void plant::init(){
        
    // servo init
    Servo0.attach(servo0Pin);
    Servo1.attach(servo1Pin);
    Servo2.attach(servo2Pin);

}

void plant::setServo0Angle(int newAngle) {
    angleServo0 = newAngle;
    Servo0.write(angleServo0);
}

void plant::setServo1Angle(int newAngle) {
    angleServo1 = map(newAngle, 0, 100, 180, 45);
    Servo1.write(angleServo1);
}

void plant::setServo2Angle(int newAngle) {
    angleServo2 = newAngle;
    Servo2.write(angleServo2);
}

/*void plant::rotateRight(int newAngleServo0, int newAngleServo1) {
	angleServo0 = map(newAngleServo0, 0, 100, 180, 0);
	angleServo1 = map(newAngleServo1, 0, 100, 180, 0);
	Servo0.write(angleServo0);
	Servo1.write(angleServo1);
}

void plant::rotateLeft(int newAngleServo1, int newAngleServo2) {
	angleServo1 = map(newAngleServo1, 0, 100, 180, 0);
	angleServo2 = map(newAngleServo2, 0, 100, 180, 0);
	Servo1.write(angleServo1);
	Servo2.write(angleServo2);
}*/