#ifndef TD_LED_ANIMATE_H
#define TD_LED_ANIMATE_H

#include "td-led.h"
#include <string>
#include <vector>

class AnimatedLED : public LED
{
public:
    // Structured command type for animations. Easier to extend than raw strings.
    enum class Cmd
    {
        SET,
        FADE,
        RESET,
        PAUSE,
        START,
        STOP
    };

    // Short aliases so callers can write `AnimatedLED::FADE` instead of
    // `AnimatedLED::AnimationCommand::FADE`.
    static constexpr Cmd SET = Cmd::SET;
    static constexpr Cmd FADE = Cmd::FADE;
    static constexpr Cmd RESET = Cmd::RESET;
    static constexpr Cmd PAUSE = Cmd::PAUSE;
    static constexpr Cmd START = Cmd::START;
    static constexpr Cmd STOP = Cmd::STOP;

    // Add an animation to the LED. `durationMs` and `startDelayMs` are milliseconds.
    // Returns the index of the added animation in the LED's queue.
    int addAnimation(Cmd command, int from, int to, unsigned long durationMs, unsigned long startDelayMs, bool rewind = false);
    // Backwards-compatible overload that accepts a string command and converts it.
    int addAnimation(const std::string &command, int from, int to, unsigned long durationMs, unsigned long startDelayMs, bool rewind = false);

    // Convert a textual command to `AnimationCommand`. Case-insensitive.
    static Cmd fromString(const std::string &command);

    // Perform animations
    void doAnimations(int &currentTime);

    void reset();

    // Query current animation index (0-based) for this LED
    int getCurrentAnimationIndex() const { return currentAnimation; }

private:
        // Animation structure (millisecond-based)
        struct LedAnimation
        {
            Cmd Command;
            int From;
            int To;
            unsigned long DurationMs;
            unsigned long StartDelayMs; // delay before this animation starts
            bool Rewind;
            unsigned long ScheduledAt; // millis() when the animation is scheduled to start (0 = not scheduled)
            unsigned long RunStartMs;  // millis() when the animation actually started (0 = not running)
        };

    std::vector<LedAnimation> animations;
    int currentAnimation = 0;

    // Calculate the current LED value during animation (animationTime in ms)
    int calculateCurrentLedValue(unsigned long animationTimeMs, const LedAnimation &anim);
};

#endif // TD_LED_ANIMATE_H