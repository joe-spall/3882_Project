
#include <Servo.h>  //servo library

#include "Arduino.h"

#define CAL_MAX 10

class photoCell{
	private:
	int photocellPin;     // the cell and 10K pulldown are connected to a0
	int photocellReading;     // the analog reading from the sensor divider
/*	int photocellBase;
	int photocellDelta;*/

/*	int photocell1Pin = A1;     // the cell and 10K pulldown are connected to a0
	int photocellReading1;     // the analog reading from the sensor divider
	int photocellBase1;
	int photocellDelta1;

	int photocell1Pin = A2;     // the cell and 10K pulldown are connected to a0
	int photocellReading2;     // the analog reading from the sensor divider
	int photocellBase2;
	int photocellDelta2;*/

	bool calibrated = false;
	int calibrateCounter = 0;

/*  	calibrated = false;
  	calibrateCounter = 0;*/
  	int photocellBase = 0;
  	int photocellDelta = 0;
/*  	photocellBase1 = 0;
  	photocellDelta1 = 0;
    photocellBase2 = 0;
  	photocellDelta3 = 0;*/

// twelve servo objects can be created on most boards
	public:
		photoCell(int photoCellPin);
		void init();
		void calibrateBaseline();
		void readPhotoCell();
		int getPhotoCellBase();
		int getPhotoCellReading();
/*		int getPhotoCellReading1();
		int getPhotoCellReading2();*/
		int getDelta();
/*		int getDelta1();		
		int getDelta2();*/
		
};