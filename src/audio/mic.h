#pragma once
#include <driver/i2s.h>

#define SAMPLE_RATE 16000
#define I2S_PORT I2S_NUM_0

class Microphone {
public:
    void init();
    bool read(int16_t* buffer, size_t samples);
};
