#ifndef IMPACT_DETECTION_H
#define IMPACT_DETECTION_H

#include "main.h"

#define IMPACT_THRESHOLD 0.15f
#define IMPACT_COOLDOWN_MS 900U

extern volatile uint32_t impact_count;
extern volatile float impact_value;
extern volatile float peak_impact;

void Impact_ProcessSample(float x, float y, float z);

#endif
