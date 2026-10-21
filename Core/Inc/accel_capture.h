#ifndef ACCEL_CAPTURE_H
#define ACCEL_CAPTURE_H

#include "main.h"

#define ACCEL_SAMPLE_COUNT 800

typedef struct
{
    uint32_t time_us;
    float x;
    float y;
    float z;
} AccelSample;

extern AccelSample accel_buffer[ACCEL_SAMPLE_COUNT];
extern volatile uint16_t accel_sample_index;
extern volatile uint8_t accel_capture_done;

void Accel_Capture(void);

#endif
