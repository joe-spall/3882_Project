#include "elegoo.h"

Elegoo robot;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    robot.init();

}

void loop() {
    Serial.println("Go");
  // put your main code here, to run repeatedly:
    
}
