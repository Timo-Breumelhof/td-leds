#ifndef TD_LED_RGB_H
#define TD_LED_RGB_H

#include <Arduino.h>
#include "td-led.h"
#include "td-led-animate.h"

// An RGB LED, wraps 3 single RGB Leds
class RGB_LED
{
public:
    AnimatedLED R;
    AnimatedLED G;
    AnimatedLED B;

    void ledR(int channel, int pin);
    void ledG(int channel, int pin);
    void ledB(int channel, int pin);

    void setupLedChannel(AnimatedLED &led);
    void Setup();
    void doAnimations(int currentTime);
};

#endif // TD_LED_RGB_H