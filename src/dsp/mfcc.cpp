#include "mfcc.h"
#include <math.h>

void MFCC::compute(int16_t* audio, float* output) {

    for (int i = 0; i < MFCC_FEATURES * MFCC_COEFFS; i++) {
        output[i] = audio[i] / 32768.0f;
    }
}
