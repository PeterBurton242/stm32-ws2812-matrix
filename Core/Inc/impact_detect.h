#ifndef IMPACT_DETECT_H
#define IMPACT_DETECT_H

#include "main.h"

typedef enum {
	IMPACT_NO = 0,
	IMPACT_YES = 1,
	IMPACT_UNDEF = 2
} ImpactResult;

void Impact_Detect_EXTI_Callback(uint16_t GPIO_Pin);
void Impact_Detect_Init(void);
ImpactResult Impact_Detection(void);

#endif
