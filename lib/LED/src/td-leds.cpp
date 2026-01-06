#include <Arduino.h>
#include "td-leds.h"          // For LED class
#include "td-leds-rgb.h"      // For RGB_LED class

#include <string>
#include <vector>


  void LEDCollection::Add(const AnimatedLED &led)
  {
    LEDS.push_back(led);
  }

  void LEDCollection::Animate(int time){
    int counter = 0;

    for(int i=0; i < LEDS.size(); i++){
        LEDS[i].doAnimations(time);
     }


  }

