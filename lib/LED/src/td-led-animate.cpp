#include <Arduino.h>

#include "td-led.h"
#include "td-led-animate.h"

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Reset all defined animations for an LED
void AnimatedLED::reset()
{
  currentAnimation = 0;
  for (auto &a : animations)
  {
    a.ScheduledAt = 0;
    a.RunStartMs = 0;
  }
}

// add an animation to the "array" of animations of this LED (enum version)
int AnimatedLED::addAnimation(Cmd command, int from, int to, unsigned long durationMs, unsigned long startDelayMs, bool rewind)
{
  LedAnimation anim;
  anim.Command = command;
  anim.From = from;
  anim.To = to;
  anim.DurationMs = durationMs;
  anim.StartDelayMs = startDelayMs;
  anim.Rewind = rewind;
  anim.ScheduledAt = 0;
  anim.RunStartMs = 0;
  animations.push_back(anim);
  return (int)animations.size() - 1;
}

// back-compat: accept a string command and convert to the enum
int AnimatedLED::addAnimation(const std::string &command, int from, int to, unsigned long durationMs, unsigned long startDelayMs, bool rewind)
{
  return addAnimation(fromString(command), from, to, durationMs, startDelayMs, rewind);
}

// Convert a textual command to `AnimationCommand`. Case-insensitive.
AnimatedLED::Cmd AnimatedLED::fromString(const std::string &command)
{
  std::string s = command;
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });

  if (s == "fade")
    return Cmd::FADE;
  if (s == "set")
    return Cmd::SET;
  if (s == "reset")
    return Cmd::RESET;
  if (s == "pause")
    return Cmd::PAUSE;
  if (s == "start")
    return Cmd::START;
  if (s == "stop")
    return Cmd::STOP;

  // default fallback
  return Cmd::SET;
}

/*
  doAnimations(int &currentTime)

  Process the animation queue for this LED. Call once per main loop and pass
  a monotonically-increasing `currentTime` counter. The function advances the
  active animation's internal time counter (`InnerTime`), initializes the LED
  value when an animation starts, interpolates values during the animation
  using `calculateCurrentLedValue()`, and finalizes the animation when its
  duration elapses. If the animation's `Rewind` flag is set the sequence will
  restart from the first animation; otherwise it advances to the next entry.

  Notes for callers:
  - "StartTime" is a delay used from the moment the animation is intialized (not a global delay)
  - `currentTime == 0` resets `currentAnimation` to the first animation.
  - Animations are processed sequentially from the `animations` vector.
  - LED output is applied via `setValue()`.
*/
void AnimatedLED::doAnimations(int &currentTime)
{
  if (currentTime == 0)
  {
    currentAnimation = 0;
    for (auto &a : animations)
    {
      a.ScheduledAt = 0;
      a.RunStartMs = 0;
    }
  }

  if (currentAnimation < (int)animations.size())
  {
    LedAnimation &currentAnim = animations[currentAnimation];

    unsigned long now = millis();

    // Schedule start time if not yet scheduled
    if (currentAnim.ScheduledAt == 0)
    {
      currentAnim.ScheduledAt = now + currentAnim.StartDelayMs;
    }

    // Not yet reached scheduled start
    if (now < currentAnim.ScheduledAt)
    {
      return;
    }

    // If run not started, initialize
    if (currentAnim.RunStartMs == 0)
    {
      currentAnim.RunStartMs = now;
      setValue(currentAnim.From);
      // If zero duration, finish immediately
      if (currentAnim.DurationMs == 0)
      {
        setValue(currentAnim.To);
        currentAnim.RunStartMs = 0;
        currentAnim.ScheduledAt = 0;
        if (currentAnim.Rewind)
        {
          currentAnimation = 0;
        }
        else
        {
          currentAnimation++;
        }
      }
      return;
    }

    unsigned long elapsed = now - currentAnim.RunStartMs;

    if (elapsed >= currentAnim.DurationMs)
    {
      setValue(currentAnim.To);
      currentAnim.RunStartMs = 0;
      currentAnim.ScheduledAt = 0;
      if (currentAnim.Rewind)
      {
        currentAnimation = 0;
      }
      else
      {
        currentAnimation++;
      }
    }
    else
    {
      int newVal = calculateCurrentLedValue(elapsed, currentAnim);
      setValue(newVal);
    }
  }
}

int AnimatedLED::calculateCurrentLedValue(unsigned long animationTimeMs, const LedAnimation &anim)
{
  if (animationTimeMs == 0)
    return anim.From;

  bool upwards = anim.To > anim.From;

  if (animationTimeMs >= anim.DurationMs)
  {
    return anim.To;
  }

  float animFraction = animationTimeMs / float(anim.DurationMs);
  int valueDifference = anim.To - anim.From;
  int ledValue = anim.From + (valueDifference * animFraction);

  if (upwards && ledValue > anim.To)
    ledValue = anim.To;
  else if (!upwards && ledValue < anim.To)
    ledValue = anim.To;

  return ledValue;
}