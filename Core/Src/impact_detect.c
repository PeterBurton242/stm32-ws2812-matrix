#include "impact_detect.h"
#include "lis3dh.h"

volatile uint8_t impact_pending = 0;
uint32_t impact_count = 0;

uint8_t source;

// Called by the STM32 GPIO EXTI callback
void Impact_Detect_EXTI_Callback(uint16_t GPIO_Pin){
    if (GPIO_Pin == GPIO_PIN_1){
        impact_pending = 1;
    }
}

void Impact_Detect_Init(void){
	impact_pending = 0;
	LIS3DH_Init();
}


ImpactResult Impact_Detection(void){
	ImpactResult result = IMPACT_UNDEF;
    // First interrupt starts the cool down
    if (impact_pending){
        impact_pending = 0;
        if (LIS3DH_ReadRegister(LIS3DH_INT1_SRC, &source) == HAL_OK){
        	result = IMPACT_YES;
        }
        else{
        	result = IMPACT_UNDEF;
        }
    }
    else{
    	result = IMPACT_NO;
    }

    return result;
}




