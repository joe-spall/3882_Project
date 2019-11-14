// State Machine version 
// depends on how many light sensors
#include "plant.h"
#include "photoCell.h"

#define PRESDIFF 30
#define TOPDIFF 30

#define PHOTORES0PIN A0
#define PHOTORES1PIN A1
#define PHOTORES2PIN A2
#define PHOTORES3PIN A3

#define abs(x) ((x)>0?(x):-(x))

enum PLANTSTATE{
	MOVETOLIGHT,
  STANDBY, 
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
      case STANDBY: {
          if(!atLightSource()) {
            currentState = MOVETOLIGHT; 
          }
        break; 
        
      }
  		case MOVETOLIGHT: {
  			if(withinMarginOfLightSource()) {
          	currentState = STANDBY; 
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
    case STANDBY: {
      plant.setServo0Angle(90); 
      plant.setServo1Angle(servo1Pos); 
      plant.setServo2Angle(90); 
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

//  	if(servo1Pos > 0){
//  		servo1Pos--;
//  		plant.setServo1Angle(servo1Pos);
//  	} 
    
  	plant.setServo2Angle(90); 
    delay(5);
}

void moveToLight() {
  int pResBotDelta = pResBot.getDelta();
  int pResTopDelta = pResTop.getDelta();
  int pResLeftDelta = pResLeft.getDelta();
  int pResRightDelta = pResRight.getDelta();
 
  
  if(pResBotDelta - pResTopDelta > TOPDIFF) {
    if(servo1Pos < 100){
      servo1Pos += 2;
    }
  } else if(pResTopDelta - pResBotDelta > TOPDIFF){
    if(servo1Pos > 0){
      servo1Pos -= 1;
    }
  }
  
  plant.setServo1Angle(servo1Pos);

  if(pResRightDelta - pResLeftDelta  > PRESDIFF){
    int ratio = (pResRightDelta - pResLeftDelta)/4;
    ratio = constrain(ratio,0, 1000);
    servo0Pos = map(ratio, 0, 400, 80, 0);
    servo2Pos = 92;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(30);
    servo0Pos = 90;
    servo2Pos = 90;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
  }

  if(pResLeftDelta - pResRightDelta > PRESDIFF){
    int ratio = (pResLeftDelta - pResRightDelta)/4;
    ratio = constrain(ratio,0, 1000);
    servo2Pos = map(ratio, 0, 400, 80, 0);
    servo0Pos = 92;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
    delay(30);
    servo2Pos = 90;
    servo0Pos = 90;
    plant.setServo0Angle(servo0Pos);
    plant.setServo2Angle(servo2Pos);
  }
  delay(5);
}
