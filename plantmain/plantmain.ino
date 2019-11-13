// State Machine version 
// depends on how many light sensors
#include "plant.h"
#include "photoCell.h"

#define PRESDIFF 30

#define PHOTORES0PIN A0
#define PHOTORES1PIN A1
#define PHOTORES2PIN A2
#define PHOTORES3PIN A3

#define abs(x) ((x)>0?(x):-(x))

enum PLANTSTATE{
	MOVETOLIGHT, 
	HOME
};

PLANTSTATE currentState;
plant plant;
photoCell pResRight(PHOTORES0PIN);
photoCell pResLeft(PHOTORES2PIN);
photoCell pResTop(PHOTORES3PIN);
photoCell pResBot(PHOTORES1PIN);
int servo0Pos = 90;
int servo1Pos = 0;
int servo2Pos = 90;

void setup() {
	Serial.begin(9600);
    plant.init();
    pResRight.calibrateBaseline();
    pResLeft.calibrateBaseline();
    pResTop.calibrateBaseline();
    pResBot.calibrateBaseline();

    plant.setServo0Angle(servo0Pos);
    plant.setServo1Angle(servo1Pos);
    plant.setServo2Angle(servo2Pos);
    currentState = HOME;
}

void loop() {
  // put your main code here, to run repeatedly:

    determineState(); 
    runState(); 
    delay(20);

}

// Determine what state you're in 
void determineState() {
	// assign photocellDelta0 to right
	// assign photocellDelta1 to left
	// assign photocellDelta2 to top
	// assign photocellDelta3 to bottom

  	// Map the index to a current state 
  	switch (currentState) {
  		case HOME: {
        	if(!atLightSource()) {
        		currentState = MOVETOLIGHT;
        	}
  			break; 
  		}
  		case MOVETOLIGHT: {
  			if(withinMarginOfLightSource()) {
          			currentState = HOME;
          	}
  			break; 
  		}
  	}
  }

// Run the current state
void runState() {
	switch (currentState) {
		case HOME: {
			returnHome(); 
			break; 
		}
		case MOVETOLIGHT: {
			moveToLight(); 
			break; 
		}
	}
}

bool atLightSource(){
  if((abs(pResTop.getDelta() - pResBot.getDelta()) > PRESDIFF) || (abs(pResRight.getDelta() - pResLeft.getDelta()) > PRESDIFF)) {return false;}
  else {return true;}
}

bool withinMarginOfLightSource(){
	
  if((abs(pResTop.getDelta() - pResBot.getDelta()) <= PRESDIFF) || (abs(pResRight.getDelta() - pResLeft.getDelta()) <= PRESDIFF)) {return true;}
  else {return false;}  
}

void returnHome() {
  	plant.setServo0Angle(90);

  	if(servo1Pos > 0){
  		servo1Pos--;
  		plant.setServo1Angle(servo1Pos);
  	} 

  	plant.setServo2Angle(90); 
}

void moveToLight() {
  if(pResBot.getDelta() - pResTop.getDelta() > PRESDIFF && servo1Pos < 100) {
    servo1Pos += 1;
  }

  // Photocell 1 greater than Photocell 3
  if(pResTop.getDelta() - pResBot.getDelta() > PRESDIFF && servo1Pos > 0){
    servo1Pos -= 1;
  }

  plant.setServo1Angle(servo1Pos);

  if(pResRight.getDelta() - pResLeft.getDelta() > PRESDIFF){
    servo0Pos = 0;
    servo2Pos = 92;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(40);
    servo0Pos = 90;
    servo2Pos = 90;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(5);
  }

  if(pResLeft.getDelta() - pResRight.getDelta() > PRESDIFF){
    servo2Pos = 0;
    servo0Pos = 92;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(40);
    servo2Pos = 90;
    servo0Pos = 90;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(5);
  }

}
