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

 /*   Serial.println("Current State:");
    Serial.println(currentState);
    Serial.println("Light Measurement Ambient");
    pResTop.readPhotoCell();
    Serial.println(pResTop.getPhotoCellReading());
    Serial.println("Light Measurement Base");
    Serial.println(pResTop.getPhotoCellBase());
    Serial.println("Light Measurement Delta");
    Serial.println(pResTop.getDelta());
    Serial.println("Servo 1 Pos");
    Serial.println(servo1Pos);*/

    Serial.print(pResTop.getDelta());
    Serial.print(", ");
    Serial.println(pResBot.getDelta());


    delay(100);

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
  if(pResBot.getPhotoCellReading() - pResTop.getPhotoCellReading() > PRESDIFF && servo1Pos < 100) {
    servo1Pos += 1;
  }

  // Photocell 1 greater than Photocell 3
  if(pResTop.getPhotoCellReading() - pResBot.getPhotoCellReading() > PRESDIFF && servo1Pos > 0){
    servo1Pos -= 1;
  }

  /*if(pResRight.getDelta() - pResLeft.getDelta() > PRESDIFF){
    servo0Pos = 0;
    servo2Pos = 180;
    Serial.println("Servo2Pos");
    Serial.println(servo2Pos);
    delay(3);
    servo0Pos = 90;
    servo2Pos = 90;
  }

  if(pResLeft.getDelta() - pResRight.getDelta() > PRESDIFF){
    servo2Pos = 0;
    servo0Pos = 180;
    Serial.println("Servo0Pos");
    Serial.println(servo0Pos);
    delay(3);
    servo2Pos = 90;
    servo0Pos = 90;
  }*/

  //plant.setServo0Angle(servo0Pos);
  plant.setServo1Angle(servo1Pos);
  //plant.setServo2Angle(servo2Pos);
}