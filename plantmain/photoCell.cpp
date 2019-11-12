#include "photoCell.h"

photoCell::photoCell(int photoCellPin){
    photocellPin = photoCellPin;
    photocellReading = analogRead(photocellPin);
/*    photocellReading1 = analogRead(photocell1Pin);
    photocellReading2 = analogRead(photocell2Pin);*/
}

void photoCell::calibrateBaseline(){
  while(calibrateCounter < CAL_MAX){
      photocellBase += analogRead(photocellPin);
/*      photocellBase1 += analogRead(photocell1Pin);
      photocellBase2 += analogRead(photocell1Pin);*/
      calibrateCounter++;
      delay(1);
  }
  photocellBase /= CAL_MAX;
  /*photocellBase1 /= CAL_MAX;
  photocellBase2 /= CAL_MAX;*/
  calibrated = true;
}

/*int photoCell::readPhotoCell(){
  photocellReading = analogRead(photocellPin);
  return photocellReading;
}*/

int photoCell::getPhotoCellReading(){
  photocellReading = analogRead(photocellPin);
	return photocellReading;
}

int photoCell::getPhotoCellBase(){
  return photocellBase;
}

/*int photoCell::getPhotoCellReading1(){
	return photocellReading1;
};
int photoCell::getPhotoCellReading2(){
	return photocellReading2;
};*/

int photoCell::getDelta(){
  photocellDelta = analogRead(photocellPin) - photocellBase;
  return photocellDelta;
}
/*int photoCell::getDelta1(){
  photocellDelta1 = photocellReading0 - photocellBase0;
  return photocellDelta1;
};
int photoCell::getDelta2(){
  photocellDelta2 = photocellReading0 - photocellBase0;
  return photocellDelta2;
}; */
