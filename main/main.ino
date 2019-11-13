/**
 * ECE 3882
 * GROUP NUMBER: 15
 * MEMBERS: JOE SPALL, VANSISH SATOOR, ERIC PEARSON, NEHA PASRICHA
 * Main code base to run the line following robot using appropriate 
 * software design techniques
 */

#include "Elegoo.h"

#define RIGHT_POS 0
#define CENTER_POS 90 
#define MIN_OBS_DIST 20
#define MIN_STATION_DIST 20
#define FORWARD_POWER_LM 0.30
#define FORWARD_POWER_RM 0.30
#define FORWARD_POWER_FAST_LM 0.35
#define FORWARD_POWER_FAST_RM 0.35
#define RFORWARD_POWER_LM 0.30
#define RFORWARD_POWER_RM 0.30
#define LFORWARD_POWER_LM 0.30
#define LFORWARD_POWER_RM 0.30
#define HRFORWARD_POWER_RM 0.5
#define HRFORWARD_POWER_LM 0.5
#define HLFORWARD_POWER_LM 0.5
#define HLFORWARD_POWER_RM 0.5
#define LEFT_CHECK_CYCLES 10
#define RIGHT_CHECK_CYCLES 5



enum ROBOT_STATE{
	FOLLOW,
	AVOID,
	STATION,
	CLEARSTATION,
	MANUFACTURING,
	IDLE
};

Elegoo robot;
ROBOT_STATE currentState;
bool finishedStop = false; 
bool finishedStation = false; 
bool finishedManufacturing = false;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    robot.init();
    robot.setCenterServo(CENTER_POS); 
    currentState = FOLLOW;

}

void loop() {
  // put your main code here, to run repeatedly:
    determineState(); 
    runState(); 

    Serial.println("Left Line Sensor:");
    Serial.println(robot.isLeftDark());
    Serial.println("Middle Line Sensor:");
    Serial.println(robot.isCenterDark());
    Serial.println("Right Line Sensor:");
    Serial.println(robot.isRightDark());
    Serial.println("Current State:");
    Serial.println(currentState);
    Serial.println("Sensor Distance:");
    Serial.println(robot.getDistance());

}

// Determine what state you're in 
void determineState() {
	switch (currentState) {
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
				currentState = CLEARSTATION; 
				finishedStation = false; 
			}
			break; 
		}
		case CLEARSTATION: {
			if(!isAtStation())
			{
				currentState = FOLLOW;
			}
			break;
		}
		case MANUFACTURING: {
			if (!isObjectToRight() && finishedManufacturing) {
				currentState = CLEARSTATION; 
				finishedManufacturing = false;
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
	switch (currentState) {
		case FOLLOW: {
			Serial.println("followline");
			followLine(); 
			break; 
		}
		case AVOID: {
			Serial.println("avoid");
			avoidObstacle(); 
			break; 
		}
		case STATION: {
			Serial.println("station");	
			waitAtStation(); 
			break; 
		}
		case CLEARSTATION: {
			Serial.println("clearhashmark");	
			goStraightFast();
			break;
		}
		case MANUFACTURING: {
			Serial.println("manufacturing");
			waitForManufacturing(); 
			break; 
		}
		case IDLE: {
			Serial.println("idle");
			goStraightFast();
			break; 
		}
	}
}

// Main State Functions
void followLine() {
	// Check infrared sensors to determine position on the line
	// Turn left or right according or move forward as appropriate
	// Check obstacles consistently here or in main? 
	if (robot.isCenterDark() && !robot.isRightDark() && !robot.isLeftDark()) {
		// go straight
		goStraight(); 
	} else if (robot.isCenterDark() && robot.isRightDark() && !robot.isLeftDark()) {
		// turn right
		turnRight(); 
	} else if (robot.isCenterDark() && !robot.isRightDark() && robot.isLeftDark()) {
		// turn left
		turnLeft(); 
	} else if (robot.isCenterDark() && robot.isRightDark() && robot.isLeftDark()) {
		// At station
		robot.stopMotor(); 
	} else if (!robot.isCenterDark() && robot.isRightDark() && !robot.isLeftDark()) {
		// turn more right
		turnHardRight(); 
	} else if (!robot.isCenterDark() && !robot.isRightDark() && robot.isLeftDark()) {
		// turn more left
		turnHardLeft(); 
	} else if (!robot.isCenterDark() && !robot.isRightDark() && !robot.isLeftDark()) {
		// turn more right
		findLine(); 
	} 

}

void avoidObstacle() {
	robot.goCenterServo(); 
	// If there is an object ahead
	while (robot.getDistance() < MIN_OBS_DIST) {
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
	if (robot.isCenterDark() && robot.isRightDark() && robot.isRightDark()) {
		robot.stopMotor(); 
		return true; 
	} else {
		return false; 
	}
}

void goStraightFast() {
	robot.goForwardMotor(FORWARD_POWER_FAST_LM,FORWARD_POWER_FAST_RM);
	Serial.println("should be going straight");
}

void goStraight() {
	robot.goForwardMotor(FORWARD_POWER_LM,FORWARD_POWER_RM);
	Serial.println("should be going straight");
}

void turnLeft() {
	robot.goLeftMotor(LFORWARD_POWER_LM,LFORWARD_POWER_RM);
	Serial.println("left");
}

void turnRight() {
	robot.goRightMotor(RFORWARD_POWER_LM,RFORWARD_POWER_RM);
	Serial.println("right");
}

void turnHardLeft() {
	robot.goLeftMotor(HLFORWARD_POWER_LM,HLFORWARD_POWER_RM);
	Serial.println("hardleft");
}

void turnHardRight() {
	robot.goRightMotor(HRFORWARD_POWER_LM,HRFORWARD_POWER_RM);
	Serial.println("hardright");
}

void findLine() {
	bool noLineFound = true; 
	int leftCount = 0; 
	int rightCount = 0; 

	while(noLineFound && leftCount < LEFT_CHECK_CYCLES) {
		robot.goLeftMotor(LFORWARD_POWER_LM,LFORWARD_POWER_RM);
		if (robot.isCenterDark() || robot.isRightDark() || robot.isLeftDark()) {
			noLineFound = false; 
		}
		delay(100);
		leftCount++; 
	}
	while (noLineFound && rightCount < RIGHT_CHECK_CYCLES) {
		robot.goRightMotor(RFORWARD_POWER_LM,RFORWARD_POWER_RM); 
		if (robot.isCenterDark() || robot.isRightDark() || robot.isLeftDark()) {
			noLineFound = false; 
		}
		delay(100);
		rightCount++; 
	}
	Serial.println("findline");
// || robot.isRightDark() || robot.isLeftDark()
}

void wait() {
	// Wait one second
	robot.stopMotor(); 
	delay(1000); 
}

bool isObjectAhead() {
	robot.goCenterServo(); 
	if (robot.getDistance() < MIN_OBS_DIST) {
		return true; 
	} 
	return false; 
}

bool isObjectToRight() {
	// Set the servo to 180 degrees to the right

	robot.goCenterServo(); 
	// Check for object
	if (robot.getDistance() < MIN_STATION_DIST) {
		// There's manufacturing happening
		return true; 
	} else {
		// Manufacturing is complete
		// Move ultrasonic sensor into central position
		robot.goCenterServo();
		wait();
		return false; 
	}

}