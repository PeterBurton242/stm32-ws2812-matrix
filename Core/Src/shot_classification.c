/*
 * shot_classification.c
 *
 *  Created on: Nov 19, 2026
 *      Author: Peter
 */
#include "shot_classification.h"
#include "impact_detect.h"
#include "make_detect.h"

uint8_t cooldown_active = 0;
uint32_t cooldown_start = 0;

ShotResult Shot_Classification_Update(void){

	uint32_t now = HAL_GetTick();
	if(now - cooldown_start >= SHOT_COOLDOWN_MS){
		// Over the cool down and count the shot
		cooldown_start = now;
		if(Make_Detection() == MAKE_YES){ // Note: ToF sensor is still polling
			return SHOT_MAKE;
		}
		else if(Impact_Detection() == IMPACT_YES){
			return SHOT_MISS;
		}
		else{
			return SHOT_NONE;
		}
	}
	else{
		return SHOT_NONE;
	}

}
