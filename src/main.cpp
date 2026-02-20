#include <Arduino.h>
#include "audio/mic.h"
#include "dsp/mfcc.h"
#include "ml/inference.h"
#include "hardware/vibrator.h"

Microphone mic;
MFCC mfcc;
Inference nn;
Vibrator vib;

int16_t audioBuffer[AUDIO_SAMPLES];
float features[MFCC_FEATURES * MFCC_COEFFS];

void setup() {

    Serial.begin(115200);

    mic.init();
    vib.init();

    if (!nn.init()) {
        Serial.println("Model init failed");
        while (1);
    }

    Serial.println("Ready");
}

void loop() {

    if (!mic.read(audioBuffer, AUDIO_SAMPLES))
        return;

    mfcc.compute(audioBuffer, features);

    float confidence;
    int result = nn.predict(features, confidence);

    if (result >= 0) {
        Serial.print("Detected word index: ");
        Serial.println(result);
        vib.trigger();
    }
}
