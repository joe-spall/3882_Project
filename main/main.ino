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
#define MIN_OBS_DIST 100
#define MIN_STATION_DIST 100
#define FORWARD_POWER_LM .25
#define FORWARD_POWER_RM .25
#define RFORWARD_POWER_LM
#define RFORWARD_POWER_RM
#define LFORWARD_POWER_LM 
#define LFORWARD_POWER_RM
#define HRFORWARD_POWER_RM .5
#define HRFORWARD_POWER_LM .5
#define HLFORWARD_POWER_LM .5
#define HLFORWARD_POWER_RM .5
#define LEFT_CHECK_CYCLES 5
#define RIGHT_CHECK_CYCLES 10


enum ROBOT_STATE:{
	FOLLOW,
	AVOID,
	STATION,
	MANUFACTURING,
	IDLE
}

Elegoo robot;
ROBOT_STATE currentState;
bool finishedStop = false; 
bool finishedStation = false; 

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

    Serial.println("Left Line Sensor:");
    Serial.println(robot.isLeftDark());
    Serial.println("Middle Line Sensor:");
    Serial.println(robot.isMiddleDark());
    Serial.println("Left Line Sensor:");
    Serial.println(robot.isLeftDark());
    Serial.println("Current State:");
    Serial.println(currentState);
    Serial.println("Sensor Distance:");
    Serial.println(robot.getDistance());

}

// Determine what state you're in 
void determineState() {
	switch currentState {
		case FOLLOW: {
			if (isObjectAhead()) {
				currentState = AVOID; 
			}
			if (isAtStation()) {
				currentState = STATION;
			}
			break; 
		}			
		case AVOID: {
			if (!isObjectAhead() && finishedStop) {
				currentState = FOLLOW; 
				finishedStop = false; 
			}
			break;
		}
		case STATION: {
			if (isObjectToRight()) {
				currentState = MANUFACTURING;
			} else if (finishedStation) {
				currentState = FOLLOW; 
				finishedStation = false; 
			}
			break; 
		}
		case MANUFACTURING: {
			if (!isObjectToRight() && finishedManufacturing) {
				currentState = FOLLOW; 
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
	if (robot.isMiddleDark() && !robot.isRightDark() && !robot.isLeftDark()) {
		// go straight
		goStraight(); 
	} else if (robot.isMiddleDark() && robot.isRightDark() && !robot.isLeftDark()) {
		// turn right
		turnRight(); 
	} else if (robot.isMiddleDark() && !robot.isRightDark() && robot.isLeftDark()) {
		// turn left
		turnLeft(); 
	} else if (robot.isMiddleDark() && robot.isRightDark() && robot.isLeftDark()) {
		// At station
		robot.stopMotor(); 
	} else if (!robot.isMiddleDark() && robot.isRightDark() && !robot.isLeftDark()) {
		// turn more right
		turnHardRight(); 
	} else if (!robot.robot.isMiddleDark() && !robot.robot.isRightDark() && robot.isLeftDark()) {
		// turn more left
		turnHardLeft(); 
	} else if (!robot.isMiddleDark() && !robot.isRightDark() && !robot.isLeftDark()) {
		// turn more right
		findLine(); 
	} 

}

void avoidObstacle() {
	robot.goCenterServo(); 
	// If there is an object ahead
	while (robot.getDistance() < MIN_DIST) {
		// call stop
		robot.stopMotor(); 
	}
	finishedStop = true; 
}

void waitAtStation() {
	robot.stopMotor(); 
	wait(); 
	finishedStation = true; 
}

void waitForManufacturing() {
	while (isObjectToRight()) {
		wait(); 
	}
	robot.goCenterServo(); 
	wait(); 
	finishedManufacturing = true; 
}

// Lower Level Functions required for Main States
bool isAtStation() {
	if (robot.isMiddleDark() && robot.isRightDark() && robot.isRightDark()) {
		robot.stopMotor(); 
		return true; 
	} else {
		return false; 
	}
}

void goStraight() {
	robot.goForwardMotor(FORWARD_POWER_LM,FORWARD_POWER_RM);
}

void turnLeft() {
	robot.goLeftMotor(LFORWARD_POWER_LM,LFORWARD_POWER_RM);
}

void turnRight() {
	robot.goRightMotor(RFORWARD_POWER_LM,RFORWARD_POWER_RM);
}

void turnHardLeft() {
	robot.goLeftMotor(HLFORWARD_POWER_LM,HLFORWARD_POWER_RM);
}

void turnHardRight() {
	robot.goRightMotor(HRFORWARD_POWER_LM,HRFORWARD_POWER_RM);
}

void findLine() {
	bool noLineFound = true; 
	int leftCount = 0; 
	int rightCount = 0; 
	while(noLineFound && leftCount < LEFT_CHECK_CYCLES) {
		robot.goLeftMotor(LFORWARD_POWER_LM,LFORWARD_POWER_RM);
		if (robot.isMiddleDark() || robot.isRightDark() || robot.isLeftDark()) {
			noLineFound = false; 
		}
		delay(100)
		leftCount++; 
	}
	while (noLineFound && rightCount < RIGHT_CHECK_CYCLES) {
		robot.goRightMotor(RFORWARD_POWER_LM,RFORWARD_POWER_RM); 
		if (robot.isMiddleDark() || robot.isRightDark() || robot.isLeftDark()) {
			noLineFound = false; 
		}
		delay(100)
		rightCount++; 
	}

}

void wait() {
	// Wait one second
	robot.stopMotor(); 
	delay(1000); 
}

bool isObjectAhead() {
	robot.goCenterServo(); 
	if (robot.getDistance() < MIN_OBS_DIST) {
		robot.stopMotor(); 
		return true; 
	} 
	return false; 
}

bool isObjectToRight() {
	// Set the servo to 180 degrees to the right
	robot.goCenterServo(RIGHT_POS); 
	// Check for object
	if (robot.getDistance() < MIN_STATION_DIST) {
		// There's manufacturing happening
		return true; 
	} else {
		// Manufacturing is complete
		// Move ultrasonic sensor into central position
		robot.goCenterServo(CENTER_POS);
		return false; 
	}

}




