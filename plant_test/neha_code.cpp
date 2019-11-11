// State Machine version 
// depends on how many light sensors
enum DIRECTION{
	TOP, 
	LEFT, 
	RIGHT, 
	BOTTOM,
	HOME
};

DIRECTION currentState;

void setup() {
    currentState = HOME;
}

void loop() {
  // put your main code here, to run repeatedly:
    determineState(); 
    runState(); 

    Serial.println("Current State:");
    Serial.println(currentState);

}

// Determine what state you're in 
void determineState() {
	// assign photocellDelta0 to right
	// assign photocellDelta1 to left
	// assign photocellDelta2 to top
	// assign photocellDelta3 to bottom

	int photoArray[3] = {photocellDelta0, photocellDelta1, photocellDelta2, photocellDelta3};
  	int maxValue = 0; 
 	int index = 0; 
  	for (int i = 0; i < 4; i++) {
    	if (photoArray[i] > maxValue) {
      	maxValue = photoArray[i]; 
      	index = i;
    	}
  	}

  	// Map the index to a current state 
  	switch (index) {
  		case 0: {
  			currentState = RIGHT; 
  			break; 
  		}
  		case 1: {
  			currentState = LEFT; 
  			break; 
  		}
  		case 2: {
  			currentState = TOP; 
  			break; 
  		}
  		case 3: {
  			currentState = BOTTOM; 
  			break; 
  		}
  		default: {
  			currentState = HOME; 
  			break; 
  		}

  	}
}

// Run the current state
void runState() {
	switch (currentState) {
		case HOME: {
			Serial.println("set to neutral");
			returnHome(); 
			break; 
		}
		case RIGHT: {
			Serial.println("right sensor activated");
			moveServo0(); 
			break; 
		}
		case LEFT: {
			Serial.println("left sensor activated");	
			moveServo2(); 
			break; 
		}
		case TOP: {
			Serial.println("top sensor activated");	
			moveServo1Right();
			break;
		}
		case BOTTOM: {
			Serial.println("bottom sensor activated");
			moveServo1Left(); 
			break; 
		}
	}
}

void returnHome() {
	servo0Pos = 90; 
  	servo1Pos = 90; 
  	servo2Pos = 90; 
  	servo0.write(servo0Pos); 
  	servo1.write(servo1Pos); 
  	servo2.write(servo2Pos); 
}

void moveServo0() {
	while (photocellReading0 < 500) {
        servo0Pos += 10; 
        photocellReading0 = analogRead(photocell0Pin);
        if (photocellReading0 < 350) {
        	break; 
        }
    }
}

void moveServo1Right() {
	while (photocellReading2 < 500) {
        servo1Pos += 10; 
        photocellReading2 = analogRead(photocell2Pin);
        if (photocellReading2 < 350) {
        	break; 
        }
    }
}

void moveServo1Left() {
	while (photocellReading3 < 500) {
        servo1Pos += 10; 
        photocellReading3 = analogRead(photocell3Pin);
        if (photocellReading3 < 350) {
        	break; 
        }
    }
}

void moveServo2() {
	while (photocellReading1 < 500) {
        servo2Pos += 10; 
        photocellReading1= analogRead(photocell1Pin);
        if (photocellReading1 < 350) {
        	break; 
        }
    }
}


