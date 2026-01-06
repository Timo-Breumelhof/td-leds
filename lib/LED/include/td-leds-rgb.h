#ifndef TD_LEDS_RGB_H
#define TD_LEDS_RGB_H

#include <Arduino.h>
#include "td-led-rgb.h"
#include <vector>

// RGBCollection class
class RGBCollection
{
public:
    // Add an RGB_LED to the collection
    void Add(const RGB_LED &rgbLed);

    // Animate all RGB LEDs in the collection
    void Animate(int &time);

    // Access an RGB_LED by index
    RGB_LED &Get(int index);

    // Safe size accessor
    int Size() const;

private:
    std::vector<RGB_LED> RGBLEDS;
};

#endif // TD_LEDS_RGB_H