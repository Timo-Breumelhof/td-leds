#ifndef TD_LED_H
#define TD_LED_H

class LED
{
public:
    int Pin;
    int Channel;
    int Value;

    void Setup(int led, int pin);
    void Setup(int led, int pin, int freq, int res);
    void setValue(int value);
};

#endif // TD_LED_H