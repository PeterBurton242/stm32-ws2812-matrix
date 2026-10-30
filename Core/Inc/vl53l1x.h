
#ifndef VL53L1X_H
#define VL53L1X_H

#include "main.h"

#define VL53L1X_ADDR       (0x29 << 1)
#define VL53L1X_MODEL_ID   0x010F

HAL_StatusTypeDef VL53L1X_ReadID(uint8_t *id);

#endif
