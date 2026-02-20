#pragma once
#include <stdint.h>

#define NUM_CLASSES 21
#define CONF_THRESHOLD 0.85f

class Inference {
public:
    bool init();
    int predict(float* input, float& confidence);
};
