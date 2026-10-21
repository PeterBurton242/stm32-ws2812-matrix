
#include "accel_capture.h"
#include "lis3dh.h"

AccelSample accel_buffer[ACCEL_SAMPLE_COUNT];

volatile uint16_t accel_sample_index = 0;
volatile uint8_t accel_capture_done = 0;

void Accel_Capture(void)
{
    accel_sample_index = 0;
    accel_capture_done = 0;

    uint32_t start_ms = HAL_GetTick();

    for (uint16_t i = 0; i < ACCEL_SAMPLE_COUNT; i++)
    {
        float x, y, z;

        if (LIS3DH_ReadAcceleration(&x, &y, &z) != HAL_OK)
        {
            break;
        }

        accel_buffer[i].time_us =
            (HAL_GetTick() - start_ms) * 1000U;

        accel_buffer[i].x = x;
        accel_buffer[i].y = y;
        accel_buffer[i].z = z;

        accel_sample_index = i + 1;

        // Approximate 400 Hz sampling
        for (volatile uint32_t delay = 0; delay < 12000; delay++)
        {
            __NOP();
        }
    }

    accel_capture_done = 1;
}
