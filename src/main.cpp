#include <Arduino.h>

#include "td-led.h"
#include "td-leds-rgb.h"
#include "td-leds.h"
#include "td-led-animate.h"
#include "td-led-animations.h"
#include "td-led-animation-set.h"

/*
======================================================
RGB LED PIN MAP (ESP32)
------------------------------------------------------
LED1: R=22, G=21, B=19
LED2: R=16, G=17, B=18
LED3: R=2,  G=23, B=4
LED4: R=25, G=26, B=27
LED5: R=32, G=33, B=14
======================================================
*/

// =====================================================
// GLOBAL LED OBJECTS
// =====================================================

RGB_LED rgbLed1;
RGB_LED rgbLed2;
RGB_LED rgbLed3;
RGB_LED rgbLed4;
RGB_LED rgbLed5;

RGBCollection rgbLeds;

// =====================================================
// ANIMATION CONTROL
// =====================================================

AnimationSet animSet1;
AnimationSet animSet2;
AnimationSet animSet3;

// Fixed update frequency: 25 Hz (40 ms)
static const unsigned long UPDATE_INTERVAL_MS = 40;
unsigned long lastUpdateMs = 0;

// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

void setupLeds();
void setupAnimations();
void updateAnimations();

// =====================================================
// ARDUINO SETUP
// =====================================================

void setup()
{
    Serial.begin(9600);

    setupLeds();
    setupAnimations();


}

// =====================================================
// ARDUINO LOOP
// =====================================================

void loop()
{
    unsigned long now = millis();


    if (now - lastUpdateMs >= UPDATE_INTERVAL_MS)
    {
        lastUpdateMs = now;
        
        updateAnimations();
    }
}

// =====================================================
// LED HARDWARE SETUP
// =====================================================

void setupLeds()
{
    rgbLed1.ledR(0, 22);
    rgbLed1.ledG(1, 21);
    rgbLed1.ledB(2, 19);
    rgbLed1.Setup();
    rgbLeds.Add(rgbLed1);

    rgbLed2.ledR(3, 16);
    rgbLed2.ledG(4, 17);
    rgbLed2.ledB(5, 18);
    rgbLed2.Setup();
    rgbLeds.Add(rgbLed2);

    rgbLed3.ledR(6, 2);
    rgbLed3.ledG(7, 23);
    rgbLed3.ledB(8, 4);
    rgbLed3.Setup();
    rgbLeds.Add(rgbLed3);

    rgbLed4.ledR(9, 25);
    rgbLed4.ledG(10, 26);
    rgbLed4.ledB(11, 27);
    rgbLed4.Setup();
    rgbLeds.Add(rgbLed4);

    rgbLed5.ledR(12, 32);
    rgbLed5.ledG(13, 33);
    rgbLed5.ledB(14, 14);
    rgbLed5.Setup();
    rgbLeds.Add(rgbLed5);
}

// =====================================================
// ANIMATION SETUP
// =====================================================

void setupAnimations()
{

    // Example: RGB fade animation on LED1
    animSet1.add(&rgbLed1.R, AnimatedLED::FADE, 0, 255, 100, 0, false);
    animSet1.add(&rgbLed1.R, AnimatedLED::FADE, 255, 0, 100, 0, false);

    animSet1.add(&rgbLed2.G, AnimatedLED::FADE, 0, 255, 200, 0, false);
    animSet1.add(&rgbLed2.G, AnimatedLED::FADE, 255, 0, 200, 0, false);

    animSet2.add(&rgbLed3.B, AnimatedLED::FADE, 0, 255, 300, 0, false);
    animSet2.add(&rgbLed3.B, AnimatedLED::FADE, 255, 0, 300, 0, false);

    animSet3.add(&rgbLed4.R, AnimatedLED::FADE, 0, 255, 400, 0, false);
    animSet3.add(&rgbLed4.R, AnimatedLED::FADE, 255, 0, 400, 0, false);

    animSet3.add(&rgbLed4.G, AnimatedLED::FADE, 0, 255, 400, 0, false);
    animSet3.add(&rgbLed4.G, AnimatedLED::FADE, 255, 0, 400, 0, false);

    animSet3.add(&rgbLed4.B, AnimatedLED::FADE, 0, 255, 400, 0, false);
    animSet3.add(&rgbLed4.B, AnimatedLED::FADE, 255, 0, 400, 0, false);
}

// =====================================================
// ANIMATION UPDATE LOOP
// =====================================================

void updateAnimations()
{
    animSet1.update();
    animSet2.update();
    animSet3.update();

    unsigned long now = millis();

    rgbLed1.doAnimations(now);
    rgbLed2.doAnimations(now);
    rgbLed3.doAnimations(now);
    rgbLed4.doAnimations(now);
    rgbLed5.doAnimations(now);


    // Restart animation set when complete
    if (animSet1.isComplete())
    {
        animSet1.reset();
    }

        // Restart animation set when complete
    if (animSet2.isComplete())
    {
        animSet2.reset();
    }

            // Restart animation set when complete
    if (animSet3.isComplete())
    {
        animSet3.reset();
    }
}
