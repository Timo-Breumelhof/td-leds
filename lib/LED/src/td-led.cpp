#include <Arduino.h>
#include "td-led.h"

#include <string>
#include <vector>

  // Setup an individual LED
  void LED::Setup(int led, int pin)
  {
    Setup(led, pin, 1000, 8);
  }

  void LED::Setup(int led, int pin, int freq, int res)
  {
    ledcSetup(led, freq, res); // ESP 32 function
    ledcAttachPin(pin, led);   // ESP 32 function
  }

  void LED::setValue(int value)
  {
    Value = value;
    ledcWrite(Channel, value);
  }


