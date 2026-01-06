#include <Arduino.h>
#include "td-leds-rgb.h"      // For RGBCollection class
#include "td-led-rgb.h"      // For RGB_LED class


  void RGBCollection::Add(const RGB_LED &rgbLed)
  {
    RGBLEDS.push_back(rgbLed);
  }

  // Accessor for RGB_LED by index
  RGB_LED &RGBCollection::Get(int index)
  {
    if (RGBLEDS.empty())
    {
      static RGB_LED dummy;
      return dummy;
    }

    if (index < 0)
    {
      index = 0;
    }

    if (index >= (int)RGBLEDS.size())
    {
      index = (int)RGBLEDS.size() - 1;
    }

    return RGBLEDS[index];
  }

  // Safe size accessor
  int RGBCollection::Size() const
  {
    return (int)RGBLEDS.size();
  }

  void RGBCollection::Animate(int &time){
    int counter = 0;

    for(int i=0; i < (int)RGBLEDS.size(); i++){
      RGBLEDS[i].doAnimations(time);
     }


  }
