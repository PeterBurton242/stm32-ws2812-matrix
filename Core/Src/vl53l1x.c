#include "vl53l1x.h"
#include "i2c.h"

HAL_StatusTypeDef VL53L1X_ReadID(uint8_t *id){
    return HAL_I2C_Mem_Read(&hi2c1, VL53L1X_ADDR, VL53L1X_MODEL_ID, I2C_MEMADD_SIZE_16BIT, id, 1, 100);
}
