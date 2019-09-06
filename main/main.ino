/**
 * ECE 3882
 * GROUP NUMBER: 15
 * MEMBERS: JOE SPALL, VANSISH SATOOR, ERIC PEARSON, NEHA PASRICHA
 * Main code base to run the line following robot using appropriate 
 * software design techniques
 */

#include <Elegoo.h>

#define RIGHT_POS 180
#define CENTER_POS 90 
#define MIN_DIST 100

enum ROBOT_STATE:{
	FOLLOW,
	AVOID,
	STATION,
	MANUFACTURING,
	IDLE
}

Elegoo robot;
ROBOT_STATE currentState;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    robot.init();
    robot.setCenterServo(CENTER_POS); 
    currentState = IDLE;

}

void loop() {
    Serial.println("Go");
  // put your main code here, to run repeatedly:
    determineState(); 
    runState(); 

    
}

// Determine what state you're in 
void determineState() {
	switch currentState {
		case FOLLOW: {
			if (isObjectAhead()) 
				currentState = AVOID; 
			if (isAtStation()) 
				currentState = STATION;
			break; 
		}			
		case AVOID: {
			if (!isObjectAhead()) 
				currentState = FOLLOW; 
			break;
		}
		case STATION: {
			if (isObjectToRight()) {
				currentState = MANUFACTURING;
			} else {
				currentState = FOLLOW; 
			}
			break; 
		}
		case MANUFACTURING: {
			if (!isObjectToRight()) {
				currentState = FOLLOW; 
			} else {
				currentState = MANUFACTURING; 
			}
			break; 
		}
		case IDLE: {
			currentState = FOLLOW; 
			break; 
		}
	}
}

// Run the current state
void runState() {
	switch currentState {
		case FOLLOW: {
			followLine(); 
			break; 
		}
		case AVOID: {
			avoidObstacle(); 
			break; 
		}
		case STATION: {
			waitAtStation(); 
			break; 
		}
		case MANUFACTURING: {
			waitForManufacturing(); 
			break; 
		}
		case IDLE: {
			wait(); 
			break; 
		}
	}
}

// Main State Functions
void followLine() {
	// Check infrared sensors to determine position on the line
	// Turn left or right according or move forward as appropriate
	// Check obstacles consistently here or in main? 
	if (isMiddleDark() && !isRightDark() && !isLeftDark()) {
		// go straight
		goStraight(); 
	} else if (isMiddleDark() && isRightDark() && !isLeftDark()) {
		// turn right
		turnRight(); 
	} else if (isMiddleDark() && !isRightDark() && isLeftDark()) {
		// turn left
		turnLeft(); 
	} else if (isMiddleDark() && isRightDark() && isRightDark()) {
		robot.stopMotor(); 
	}
}

void avoidObstacle() {
	robot.goCenterServo(); 
	// If there is an object ahead
	while (robot.getDistance() < MIN_DIST) {
		// call stop
		robot.stopMotor(); 
	}
}

void waitAtStation() {
	robot.stopMotor(); 
	// Once all three infrared sensors are lit, we enter here
	// call check manufacturing 
	if (isObjectToRight() == false) {
		// wait for one second
		wait(); 
	} else {
		// call wait for manufacturing
		waitForManufacturing(); 
	}
	followLine(); 
}

void waitForManufacturing() {
	while (isObjectToRight() == true) {
		robot.stopMotor(); 
	}
	followLine(); 
}

// Lower Level Functions required for Main States
bool isAtStation() {

}

void goStraight() {

}

void turnLeft() {

}

void turnRight() {

}

void wait() {
	// Wait one second
	int t = 0; 
	while (t < 100) {
		robot.stopMotor(); 
		t = t+1; 
	}
}

bool isObjectAhead() {
	robot.setCenterServo(0); 
	if (robot.getDistance() < 10) {
		robot.stopMotor(); 
		return true; 
	} 
	return; 
}

bool isObjectToRight() {
	// Set the servo to 90 degrees to the right
	robot.setPosServo(char 90); 
	// Check for object
	int dist = robot.getDistance();
	if (dist < 10) {
		// There's manufacturing happening
		return true; 
	} else {
		// Manufacturing is complete
		// Move ultrasonic sensor into central position
		robot.setCenterServo(0);
		return false; 
	}

}




