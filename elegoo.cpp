#include "elegoo.h"


Elegoo::Elegoo(){

}

// Motor Commands

Elegoo::motorForward(float pwrLeft, float pwrRight){
	if(verifyMotorPwr(pwrLeft,pwrRight)){
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
		digitalWrite(IN3, LOW);
		digitalWrite(IN4, HIGH);
		motorSpeedWrite(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move forward");
	}
}

Elegoo::motorBackward(float pwrLeft, float pwrRight){
	if(verifyMotorPwr(pwrMotorA,pwrMotorB)){
		digitalWrite(IN1, LOW);
		digitalWrite(IN2, HIGH);
		digitalWrite(IN3, HIGH);
		digitalWrite(IN4, LOW);
		motorSpeedWrite(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move backward");
	}
}

Elegoo::motorLeft(float pwrLeft, float pwrRight){
	if(verifyMotorPwr(pwrMotorA,pwrMotorB)){
  		digitalWrite(IN1, LOW);
  		digitalWrite(IN2, HIGH);
  		digitalWrite(IN3, LOW);
  		digitalWrite(IN4, HIGH); 
		motorSpeedWrite(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move left");
	}
}

Elegoo::motorRight(float pwrLeft, float pwrRight){
	if(verifyMotorPwr(pwrMotorA,pwrMotorB)){
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
		digitalWrite(IN3, HIGH);
		digitalWrite(IN4, LOW);
		motorSpeedWrite(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move right");
	}
}

Elegoo::motorStop(){
	digitalWrite(LEFT_MOTORS,0);
	digitalWrite(RIGHT_MOTORS,0);
}

bool verifyMotorPwr(float pwrLeft, float pwrRight){
	bool motorPwrValid = true;
	if(pwrLeft > 1){
		motorPwrValid = false;
		Serial.println("Error: Left Motor Power exceeded 1");
	}
	if(pwrRight > 1){
		motorPwrValid = false;
		Serial.println("Error: Right Motor Power exceeded 1");
	}
	if(pwrLeft < 0){
		motorPwrValid = false;
		Serial.println("Error: Left Motor Power under 0");
	}
	if(pwrRight < 0){
		motorPwrValid = false;
		Serial.println("Error: Right Motor Power under 0");
	}
	return motorPwrValid;
}

void motorSpeedWrite(float pwrLeft, float pwrRight){
	int leftWriteValue = pwrLeft * 255;
	int rightWriteValue = pwrRight * 255;
	analogWrite(LEFT_MOTORS, leftWriteValue);
	analogWrite(RIGHT_MOTORS, rightWriteValue);
}