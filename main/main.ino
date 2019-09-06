/**
 * ECE 3882
 * GROUP NUMBER: 15
 * MEMBERS: JOE SPALL, VANSISH SATOOR, ERIC PEARSON, NEHA PASRICHA
 * Main code base to run the line following robot using appropriate 
 * software design techniques
 */

#include <Elegoo.h>

// Main State Functions
void followLine() {
	// Check infrared sensors to determine position on the line
	// Turn left or right according or move forward as appropriate
	// Check obstacles consistently here or in main? 
	if (isMiddleDark() && !isRightDark() && !isLeftDark()) {
		// go straight
	} else if (isMiddleDark() && isRightDark() && !isLeftDark()) {
		// turn right
		turnRight(); 
	} else if (isMiddleDark() && !isRightDark() && isLeftDark()) {
		// turn left
		turnLeft(); 
	} else if (isMiddleDark() && isRightDark() && isRightDark()) {
		// you're at a station
		waitAtStation(); 
	}



}

void avoidObstacle() {
	// If there is an object ahead
	while (Elegoo::getDistance() < 10) {
		// call stop
		Elegoo::stopMotor(); 
	}
	// Once removed, return to following the line
	followLine(); 

}

void waitAtStation() {
	Elegoo::stopMotor(); 
	// Once all three infrared sensors are lit, we enter here
	// call check maintenance 
	if (isObjectToRight() == false) {
		// wait for one second
		wait(); 
	} else {
		// call wait for maintenance
		waitForMaintenance(); 
	}
	followLine(); 
}

void waitForMaintenance() {
	while (isObjectToRight() == true) {
		Elegoo::stopMotor(); 
	}
	followLine(); 
}

// Lower Level Functions required for Main States
void turnLeft() {

}

void turnRight() {

}

void wait() {
	// Wait one second
	int t = 0; 
	while (t < 100) {
		Elegoo::stopMotor(); 
		t = t+1; 
	}
}

void isObjectAhead() {
	Elegoo::setCenterServo(0); 
	if (Elegoo::getDistance() < 10) {
		Elegoo::stopMotor(); 
		avoidObstacle(); 
	}
}

bool isObjectToRight() {
	// Set the servo to 90 degrees to the right
	Elegoo::setPosServo(char 90); 
	// Check for object
	int dist = Elegoo::getDistance();
	if (dist < 10) {
		// There's maintenance happening
		return true; 
	} else {
		// Maintenance is complete
		// Move ultrasonic sensor into central position
		Elegoo::setCenterServo(0);
		return false; 
	}

}

main() {
	// Switch statement to switch between states



}




