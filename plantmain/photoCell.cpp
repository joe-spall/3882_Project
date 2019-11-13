#include "photoCell.h"

photoCell::photoCell(int photoCellPin){
    photocellPin = photoCellPin;
    photocellReading = analogRead(photocellPin);
}

void photoCell::calibrateBaseline(){
  while(calibrateCounter < CAL_MAX){
      photocellBase += analogRead(photocellPin);
      calibrateCounter++;
      delay(1);
  }
  photocellBase /= CAL_MAX;
  calibrated = true;
}

int photoCell::getPhotoCellReading(){
  photocellReading = analogRead(photocellPin);
	return photocellReading;
}

int photoCell::getPhotoCellBase(){
  return photocellBase;
}

int photoCell::getDelta(){
  photocellDelta = analogRead(photocellPin) - photocellBase;
  return photocellDelta;
}
