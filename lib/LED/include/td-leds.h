#ifndef TD_LEDS_H
#define TD_LEDS_H

#include <Arduino.h>
#include <vector>
#include "td-led.h"
#include "td-led-animate.h"


// LEDCollection class
class LEDCollection
{
public:
    // Add an AnimatedLED to the collection
    void Add(const AnimatedLED &led);

    // Animate all LEDs in the collection
    void Animate(int time);

private:
    std::vector<AnimatedLED> LEDS;
};

#endif // TD_LEDS_H