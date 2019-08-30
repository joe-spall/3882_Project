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



}

void avoidObstacle() {

	// If obstacle detected moves into here 
	// Call stop motors until ultrasonic sensor no longer detects object

}

void waitAtStation() {

	// Once all three infrared sensors are lit, we enter here
	// call check maintenance 
	
	if (checkMaintenance() == false) {
		// wait for one second
	} else {
		// call wait for maintenance
	}

}

bool waitForMaintenance() {

}

// Lower Level Functions required for Main States

void turnLeft() {

}

void turnRight() {

}

void stop() {

}

void isObjectAhead() {


}

void isObjectToRight() {

}

bool checkMaintenance() {

}




