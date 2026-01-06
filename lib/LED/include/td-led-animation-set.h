#ifndef TD_LED_ANIMATE_SET_H
#define TD_LED_ANIMATE_SET_H

#include <vector>
#include <utility>
#include "td-led-animate.h"

// A lightweight container that holds a set of per-LED animations.
// Each added animation is started when `update()` is called the first time
// and the class tracks the started animation indices so it can report
// completion or be reset.
class AnimationSet
{
public:
    struct Action
    {
        AnimatedLED *Led = nullptr;
        AnimatedLED::Cmd Command = AnimatedLED::Cmd::SET;
        int From = 0;
        int To = 0;
        unsigned long DurationMs = 0;
        unsigned long StartDelayMs = 0;
        bool Rewind = false;
    };

    // Add an action to the set (no immediate start)
    void add(AnimatedLED *led, AnimatedLED::Cmd cmd, int from, int to, unsigned long durationMs, unsigned long startDelayMs = 0, bool rewind = false);

    // Reset internal state and optionally reset LEDs
    void reset();

    // Start pending actions (only once) and poll for completion on subsequent calls
    void update();

    // Query whether the set has finished (all started animations completed)
    bool isComplete() const;

private:
    std::vector<Action> actions;
    // pairs of (Led, startedAnimationIndex)
    std::vector<std::pair<AnimatedLED*, int>> startedIndices;
    bool started = false;
};

#endif // TD_LED_ANIMATE_SET_H
