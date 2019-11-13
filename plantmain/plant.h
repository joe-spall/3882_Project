#include <Servo.h>  //servo library

class plant{
	private:
		int angleServo0 = 0;
		int angleServo1 = 0;
		int angleServo2 = 0;
		int servo0Pin = 10;
		int servo1Pin = 9;
		int servo2Pin = 11;
	public:
		plant();
		Servo Servo0;
		Servo Servo1;
		Servo Servo2;
		void init();
		void setServo0Angle(int newAngle);
		void setServo1Angle(int newAngle);
		void setServo2Angle(int newAngle);
		void rotateRight(int newAngleServo2, int newAngleServo3);
		void rotateLeft(int newAngleServo1, int newAngleServo2);

};