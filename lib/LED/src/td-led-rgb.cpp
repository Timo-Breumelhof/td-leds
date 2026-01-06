#include <Arduino.h>
#include "td-led.h"          // For the LED class
#include "td-led-rgb.h"      // For the RGB_LED class
#include "td-led-animate.h"  // For LedAnimator

#include <string>
#include <vector>

// Implementations for RGB_LED declared in header

void RGB_LED::ledR(int channel, int pin)
{
    R.Channel = channel;
    R.Pin = pin;
}

void RGB_LED::ledG(int channel, int pin)
{
    G.Channel = channel;
    G.Pin = pin;
}

void RGB_LED::ledB(int channel, int pin)
{
    B.Channel = channel;
    B.Pin = pin;
}

// Setup one channel of an RGB LED
void RGB_LED::setupLedChannel(AnimatedLED &led)
{
    led.Setup(led.Channel, led.Pin);
}

// Setup an RGB LED
void RGB_LED::Setup()
{
    setupLedChannel(R);
    setupLedChannel(G);
    setupLedChannel(B);
}

// Delegate animations to each channel
void RGB_LED::doAnimations(int currentTime)
{
    R.doAnimations(currentTime);
    G.doAnimations(currentTime);
    B.doAnimations(currentTime);
}
