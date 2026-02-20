#include "mic.h"

void Microphone::init() {

    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 4,
        .dma_buf_len = 256,
        .use_apll = false
    };

    i2s_pin_config_t pins = {
        .bck_io_num = 26,
        .ws_io_num = 25,
        .data_out_num = -1,
        .data_in_num = 33
    };

    i2s_driver_install(I2S_PORT, &config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pins);
}

bool Microphone::read(int16_t* buffer, size_t samples) {
    size_t bytesRead;
    i2s_read(I2S_PORT, buffer, samples * sizeof(int16_t),
             &bytesRead, portMAX_DELAY);
    return bytesRead > 0;
}
