#include "elegoo.h"

Elegoo::Elegoo(char currPosServo, char centerPosServo){
	// Motor init
	pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(LEFT_MOTORS_PIN, OUTPUT);
  pinMode(RIGHT_MOTORS_PIN, OUTPUT);
  stopMotor();
	// Ultrasonic init
	pinMode(ECHO_PIN,INPUT);
	pinMode(TRIG_PIN,OUTPUT);
	// Ultrasonic servo init
	ultrasonicServo.attach(SERVO_PIN);
	goCenterServo();
	// Light sensor init
	pinMode(LIGHT_RIGHT_PIN,INPUT);
	pinMode(LIGHT_CENTER_PIN,INPUT);
	pinMode(LIGHT_LEFT_PIN,INPUT);

  irrecv = IRrecv(RECV_REMOTE_PIN);
	irrecv.enableIRIn();
}

// Motor Commands

void Elegoo::goForwardMotor(float pwrLeft, float pwrRight){
	if(verifyPwrMotor(pwrLeft,pwrRight)){
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);
		writeSpeedMotor(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move forward");
	}
}

void Elegoo::goBackwardMotor(float pwrLeft, float pwrRight){
	if(verifyPwrMotor(pwrLeft,pwrRight)){
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);
		writeSpeedMotor(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move backward");
	}
}

void Elegoo::goLeftMotor(float pwrLeft, float pwrRight){
	if(verifyPwrMotor(pwrLeft,pwrRight)){
  		digitalWrite(IN1_PIN, LOW);
  		digitalWrite(IN2_PIN, HIGH);
  		digitalWrite(IN3_PIN, LOW);
  		digitalWrite(IN4_PIN, HIGH); 
		  writeSpeedMotor(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move left");
	}
}

void Elegoo::goRightMotor(float pwrLeft, float pwrRight){
	if(verifyPwrMotor(pwrLeft,pwrRight)){
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);
		writeSpeedMotor(pwrLeft,pwrRight);
	} else{
		Serial.println("Error: Cannot move right");
	}
}

void Elegoo::stopMotor(){
	digitalWrite(LEFT_MOTORS_PIN,0);
	digitalWrite(RIGHT_MOTORS_PIN,0);
}

// pwrLeft, pwrRight in precentage from 0 to 1
bool Elegoo::verifyPwrMotor(float pwrLeft, float pwrRight){
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

void Elegoo::writeSpeedMotor(float pwrLeft, float pwrRight){
	int leftWriteValue = pwrLeft * 255;
	int rightWriteValue = pwrRight * 255;
	analogWrite(LEFT_MOTORS_PIN, leftWriteValue);
	analogWrite(RIGHT_MOTORS_PIN, rightWriteValue);
}

// Ultrasonic Commands

// Ultrasonic distance measurement
int Elegoo::getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return (int)pulseIn(ECHO_PIN, HIGH) / 58;
}


// Ultrasonic Servo Commands

// Ultrasonic Servo Centering Commands
char Elegoo::getCenterServo() {
	return centerPosServo;
}

void Elegoo::setCenterServo(char centerAngle) {
	centerPosServo = centerAngle;
}

void Elegoo::goCenterServo() {
	setPosServo(getCenterServo());
}

// Ultrasonic Servo Position commands
char Elegoo::getPosServo() {
	return currPosServo;
}

void Elegoo::setPosServo(char angle) {
	if(verifyPosServo(angle)){
		currPosServo = angle;
		ultrasonicServo.write(currPosServo);
	} else{
		Serial.println("Error: Cannot move Ultrasonic Servo");
	}
	
}

// Angle in degrees from 0 to 180
bool Elegoo::verifyPosServo(char angle) {
	bool servoPosValid = true;
	if(angle < 0){
		servoPosValid = false;
		Serial.println("Error: Servo angle under 0");
	}
	if(angle > 180){
		servoPosValid = false;
		Serial.println("Error: Servo angle over 180");
	}
	return servoPosValid;
}

// Light Sensor Commands
bool Elegoo::isRightDark(){
	return digitalRead(LIGHT_RIGHT_PIN);
}

bool Elegoo::isMiddleDark(){
	return digitalRead(LIGHT_CENTER_PIN);
}

bool Elegoo::isLeftDark(){
	return digitalRead(LIGHT_LEFT_PIN);
}

// IR Remote Commands
void Elegoo::setStateRemote(){
	if (irrecv.decode(&resultsRemote)){ 
    	unsigned long valueRemote = resultsRemote.value;
    	// DEBUG
    	Serial.println(valueRemote);
    	//
    	irrecv.resume();
    	switch(valueRemote){
      		case FORWARD_CODE:{
      			stateRemote = FORWARD;
      			break;
      		}
      		case BACKWARD_CODE:{
      			stateRemote = BACKWARD;
      			break;
      		}
      		case LEFT_CODE:{
      			stateRemote = LEFT;
      			break;
      		}
      		case RIGHT_CODE:{
      			stateRemote = RIGHT;
      			break;
      		}
      		default: break;
      	}
  	}
}

IR_REMOTE_STATE Elegoo::getStateRemote(){
	return stateRemote;
}