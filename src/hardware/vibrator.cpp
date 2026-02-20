#include "vibrator.h"

void Vibrator::init() {
    pinMode(VIB_PIN, OUTPUT);
    digitalWrite(VIB_PIN, LOW);
}

void Vibrator::trigger() {

    unsigned long now = millis();
    if (now - lastTrigger < COOLDOWN_MS)
        return;

    digitalWrite(VIB_PIN, HIGH);
    delay(80);
    digitalWrite(VIB_PIN, LOW);

    lastTrigger = now;
}
