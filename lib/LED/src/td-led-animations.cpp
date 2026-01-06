#include "td-led-animations.h"

// Creates a fading effect for an LED between two values
void fadeInOut(AnimatedLED &led, unsigned long durationMs, unsigned long &timeMs)
{
    led.addAnimation(AnimatedLED::FADE, 0, 255, durationMs, timeMs);
    timeMs = timeMs + durationMs;
    led.addAnimation(AnimatedLED::FADE, 255, 0, durationMs, timeMs);
    timeMs = timeMs + durationMs;
}

// Creates a repeating fade effect for an LED
void fadeInOutRepeat(AnimatedLED &led, int from, int to, unsigned long durationMs, unsigned long startMs)
{
    led.addAnimation(AnimatedLED::FADE, from, to, durationMs, startMs);
    // start reverse after first animation and set rewind=true
    led.addAnimation(AnimatedLED::FADE, to, from, durationMs, startMs + durationMs, true);
}
