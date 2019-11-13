
#include <Servo.h>  //servo library

#include "Arduino.h"

#define CAL_MAX 10

class photoCell{
	private:
	int photocellPin;     // the cell and 10K pulldown are connected to a0
	int photocellReading;     // the analog reading from the sensor divider

	bool calibrated = false;
	int calibrateCounter = 0;

  	int photocellBase = 0;
  	int photocellDelta = 0;

// twelve servo objects can be created on most boards
	public:
		photoCell(int photoCellPin);
		void init();
		void calibrateBaseline();
		void readPhotoCell();
		int getPhotoCellBase();
		int getPhotoCellReading();
		int getDelta();
		
};