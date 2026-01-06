#include <Arduino.h>
#include "timo_design_potmeter.h"

// Potentiometer
const int potPin = 13;
int potValue = 0;
int loopDelay = 2;

int potRead();

int potRead()
{

  potValue = analogRead(potPin);
  Serial.println(potValue);
  float potSpeed = potValue / 100;

  loopDelay = floor(potSpeed);

  return loopDelay;
  

}
