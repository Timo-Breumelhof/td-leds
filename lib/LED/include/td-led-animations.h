#ifndef TD_LED_ANIMATIONS_H
#define TD_LED_ANIMATIONS_H

#include "td-led-animate.h"

// durations are in milliseconds; `time` is a millis offset used as start time
void fadeInOut(AnimatedLED &led, unsigned long durationMs, unsigned long &timeMs);
void fadeInOutRepeat(AnimatedLED &led, int from, int to, unsigned long durationMs, unsigned long startMs);

#endif // TD_LED_ANIMATIONS_H
