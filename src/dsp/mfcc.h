#pragma once
#include <stdint.h>

#define AUDIO_SAMPLES 16000
#define MFCC_FEATURES 49
#define MFCC_COEFFS 10

class MFCC {
public:
    void compute(int16_t* audio, float* output);
};
