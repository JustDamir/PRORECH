#include "inference.h"
#include "model_data.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

namespace {
    const tflite::Model* model = nullptr;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* input;
    TfLiteTensor* output;

    constexpr int tensorArenaSize = 60 * 1024;
    uint8_t tensorArena[tensorArenaSize];
}

bool Inference::init() {

    model = tflite::GetModel(g_model);
    if (model->version() != TFLITE_SCHEMA_VERSION) return false;

    static tflite::AllOpsResolver resolver;

    static tflite::MicroInterpreter staticInterpreter(
        model, resolver, tensorArena, tensorArenaSize);

    interpreter = &staticInterpreter;

    if (interpreter->AllocateTensors() != kTfLiteOk) return false;

    input = interpreter->input(0);
    output = interpreter->output(0);

    return true;
}

int Inference::predict(float* features, float& confidence) {

    for (int i = 0; i < input->bytes / sizeof(float); i++)
        input->data.f[i] = features[i];

    if (interpreter->Invoke() != kTfLiteOk)
        return -1;

    int bestIndex = 0;
    confidence = 0;

    for (int i = 0; i < NUM_CLASSES; i++) {
        float val = output->data.f[i];
        if (val > confidence) {
            confidence = val;
            bestIndex = i;
        }
    }

    if (confidence > CONF_THRESHOLD)
        return bestIndex;

    return -1;
}
