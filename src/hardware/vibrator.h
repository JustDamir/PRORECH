#pragma once
#include <Arduino.h>

#define VIB_PIN 4
#define COOLDOWN_MS 2000

class Vibrator {
public:
    void init();
    void trigger();

private:
    unsigned long lastTrigger = 0;
};
