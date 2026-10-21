
#include "lis3dh.h"
#include "i2c.h"

HAL_StatusTypeDef LIS3DH_ReadID(uint8_t *id)
{
    HAL_StatusTypeDef status;

    // Try address 0x18 first
    status = HAL_I2C_Mem_Read(
        &hi2c1,
        LIS3DH_ADDR,
        LIS3DH_WHO_AM_I,
        I2C_MEMADD_SIZE_8BIT,
        id,
        1,
        100
    );

    return status;
}


HAL_StatusTypeDef LIS3DH_Init(void)
{
    uint8_t value;
    HAL_StatusTypeDef status;

    // CTRL_REG1:
    // 400 Hz output data rate
    // Normal/HR mode (LPen = 0)
    // X, Y, Z enabled
    value = 0x77;

    status = HAL_I2C_Mem_Write(
        &hi2c1,
        LIS3DH_ADDR,
        LIS3DH_CTRL_REG1,
        I2C_MEMADD_SIZE_8BIT,
        &value,
        1,
        100
    );

    if (status != HAL_OK)
        return status;

    // CTRL_REG4:
    // Block data update enabled
    // +/-16g scale
    // High-resolution enabled
    value = 0xB8;

    status = HAL_I2C_Mem_Write(
        &hi2c1,
        LIS3DH_ADDR,
        LIS3DH_CTRL_REG4,
        I2C_MEMADD_SIZE_8BIT,
        &value,
        1,
        100
    );

    return status;
}


HAL_StatusTypeDef LIS3DH_ReadAcceleration(
    float *x,
    float *y,
    float *z)
{
    uint8_t data[6];

    // Read all three axes in one I2C transaction
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        &hi2c1,
        LIS3DH_ADDR,
        LIS3DH_OUT_X_L | 0x80,
        I2C_MEMADD_SIZE_8BIT,
        data,
        6,
        100
    );

    if (status != HAL_OK)
        return status;

    // Combine low and high bytes
    int16_t raw_x = (int16_t)(
        ((uint16_t)data[1] << 8) | data[0]
    );

    int16_t raw_y = (int16_t)(
        ((uint16_t)data[3] << 8) | data[2]
    );

    int16_t raw_z = (int16_t)(
        ((uint16_t)data[5] << 8) | data[4]
    );

    // High-resolution mode: 12-bit left-justified
    raw_x >>= 4;
    raw_y >>= 4;
    raw_z >>= 4;

    // +/-16g, high-resolution: nominal 12 mg/LSB
    *x = raw_x * 0.012f;
    *y = raw_y * 0.012f;
    *z = raw_z * 0.012f;

    return HAL_OK;
}


HAL_StatusTypeDef LIS3DH_DataReady(uint8_t *ready)
{
    uint8_t status_reg = 0;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        &hi2c1,
        LIS3DH_ADDR,
        LIS3DH_STATUS_REG,
        I2C_MEMADD_SIZE_8BIT,
        &status_reg,
        1,
        100
    );

    if (status != HAL_OK)
    {
        return status;
    }

    *ready = (status_reg & LIS3DH_ZYXDA) != 0;

    return HAL_OK;
}



