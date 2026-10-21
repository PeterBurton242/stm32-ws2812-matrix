#include "impact_detection.h"
#include <math.h>

volatile uint32_t impact_count = 0;
volatile float impact_value = 0.0f;
volatile float peak_impact = 0.0f;

static uint32_t last_impact_time = 0;
static uint8_t first_impact = 1;

void Impact_ProcessSample(float x, float y, float z)
{
    float magnitude = sqrtf( x * x + y * y + z * z);

    impact_value = fabsf(magnitude - 1.0f); //subtract 1 G to account for earths pull

    if (impact_value > peak_impact) // keep track of impact peak
    {
        peak_impact = impact_value;
    }

    uint32_t now = HAL_GetTick(); // time stamp

    if (impact_value >= IMPACT_THRESHOLD)
    {
    	// ensure new impact is after the cooldown period
        if (first_impact || (uint32_t)(now - last_impact_time) >= IMPACT_COOLDOWN_MS)
        {
            impact_count++;
            last_impact_time = now;
            first_impact = 0;
        }
    }
}
