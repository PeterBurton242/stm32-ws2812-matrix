
#include "lis3dh.h"
#include "i2c.h"
#include "stm32l4xx_hal.h"


HAL_StatusTypeDef LIS3DH_EnableImpactInterrupt(void);

HAL_StatusTypeDef LIS3DH_WriteRegister(uint8_t reg, uint8_t value){
    return HAL_I2C_Mem_Write(
        &hi2c1,
        0x19 << 1,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        &value,
        1,
        100
    );
}

HAL_StatusTypeDef LIS3DH_ReadRegister(uint8_t reg, uint8_t *value){
    return HAL_I2C_Mem_Read(
        &hi2c1,
        0x19 << 1,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        value,
        1,
        100
    );
}


HAL_StatusTypeDef LIS3DH_ReadID(uint8_t *id){
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


HAL_StatusTypeDef LIS3DH_Init(void){
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
    if (status != HAL_OK)
        return status;

    status = LIS3DH_EnableImpactInterrupt();

    return status;
}


HAL_StatusTypeDef LIS3DH_ReadAcceleration(float *x, float *y, float *z){
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
    int16_t raw_x = (int16_t)(((uint16_t)data[1] << 8) | data[0]);

    int16_t raw_y = (int16_t)(((uint16_t)data[3] << 8) | data[2]);

    int16_t raw_z = (int16_t)(((uint16_t)data[5] << 8) | data[4]);

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


HAL_StatusTypeDef LIS3DH_DataReady(uint8_t *ready){
    uint8_t status_reg = 0;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read( &hi2c1, LIS3DH_ADDR, LIS3DH_STATUS_REG, I2C_MEMADD_SIZE_8BIT, &status_reg, 1, 100);
    if (status != HAL_OK){
        return status;
    }

    *ready = (status_reg & LIS3DH_ZYXDA) != 0;

    return HAL_OK;
}



HAL_StatusTypeDef LIS3DH_EnableImpactInterrupt(void){
    HAL_StatusTypeDef status;
    uint8_t ctrl5;
    uint8_t reference;
    uint8_t int_source;

    // Disable interrupt output during configuration
    status = LIS3DH_WriteRegister(LIS3DH_CTRL_REG3, 0x00);
    if (status != HAL_OK) return status;

    // Enable high-pass filter for interrupt generator 1
    // Normal mode, default cutoff, HP_IA1 enabled
    status = LIS3DH_WriteRegister(LIS3DH_CTRL_REG2, 0x01);
    if (status != HAL_OK) return status;

    // Reset high-pass filter reference
    status = LIS3DH_ReadRegister(0x26, &reference);
    if (status != HAL_OK) return status;

    // Configure interrupt generator 1
    // OR combination of high/low events on X, Y, Z
    status = LIS3DH_WriteRegister(LIS3DH_INT1_CFG, 0x2A);
    if (status != HAL_OK) return status;

    // Set impact threshold
    // 0x02 = approximately 0.372g at +/-16g
    status = LIS3DH_WriteRegister(LIS3DH_INT1_THS, 0x03);
    if (status != HAL_OK) return status;

    // No minimum duration required
    status = LIS3DH_WriteRegister(LIS3DH_INT1_DURATION, 0x00);
    if (status != HAL_OK) return status;

    // Enable latched interrupt mode
    status = LIS3DH_ReadRegister(LIS3DH_CTRL_REG5, &ctrl5);
    if (status != HAL_OK) return status;

    ctrl5 |= 0x08;  // LIR_INT1

    status = LIS3DH_WriteRegister(LIS3DH_CTRL_REG5, ctrl5);
    if (status != HAL_OK) return status;

    // Clear any pending interrupt
    status = LIS3DH_ReadRegister(LIS3DH_INT1_SRC, &int_source);
    if (status != HAL_OK) return status;

    // Route interrupt generator 1 to INT1 only
    status = LIS3DH_WriteRegister(LIS3DH_CTRL_REG3, 0x40);
    if (status != HAL_OK) return status;

    return HAL_OK;
}





