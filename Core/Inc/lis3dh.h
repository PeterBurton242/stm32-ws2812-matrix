
#ifndef LIS3DH_H
#define LIS3DH_H

#include "main.h"

// I2C address
#define LIS3DH_ADDR          (0x19 << 1)

// Register addresses
#define LIS3DH_WHO_AM_I      0x0F
#define LIS3DH_CTRL_REG1     0x20
#define LIS3DH_CTRL_REG4     0x23
#define LIS3DH_OUT_X_L       0x28
#define LIS3DH_STATUS_REG 0x27
#define LIS3DH_ZYXDA      0x08
#define LIS3DH_ZYXOR      0x80

// Functions
HAL_StatusTypeDef LIS3DH_ReadID(uint8_t *id);
HAL_StatusTypeDef LIS3DH_Init(void);
HAL_StatusTypeDef LIS3DH_DataReady(uint8_t *ready);
HAL_StatusTypeDef LIS3DH_ReadAcceleration(
    float *x,
    float *y,
    float *z
);

#endif

