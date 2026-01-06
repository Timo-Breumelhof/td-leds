#include "td-led-animation-set.h"
#include <Arduino.h>

void AnimationSet::add(AnimatedLED *led, AnimatedLED::Cmd cmd, int from, int to, unsigned long durationMs, unsigned long startDelayMs, bool rewind)
{
    Action a;
    a.Led = led;
    a.Command = cmd;
    a.From = from;
    a.To = to;
    a.DurationMs = durationMs;
    a.StartDelayMs = startDelayMs;
    a.Rewind = rewind;
    actions.push_back(a);
}

void AnimationSet::reset()
{
    started = false;
    startedIndices.clear();
    // Reset each underlying LED's animation queue as well
    for (auto &a : actions)
    {
        if (a.Led)
            a.Led->reset();
    }
}

void AnimationSet::update()
{
    if (started)
    {
        // check completion
        return;
    }

    // start all actions by adding animations to each LED
    started = true;
    startedIndices.clear();
    for (auto &a : actions)
    {
        if (!a.Led)
            continue;
        int idx = a.Led->addAnimation(a.Command, a.From, a.To, a.DurationMs, a.StartDelayMs, a.Rewind);
        startedIndices.push_back(std::make_pair(a.Led, idx));
    }
}

bool AnimationSet::isComplete() const
{
    if (!started) return false;
    for (auto &p : startedIndices)
    {
        AnimatedLED *led = p.first;
        int idx = p.second;
        if (!led) continue;
        if (!(led->getCurrentAnimationIndex() > idx))
            return false;
    }
    return true;
}
