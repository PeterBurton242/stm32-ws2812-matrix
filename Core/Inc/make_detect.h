/*
 * make_detect.h
 *
 *  Created on: Nov 10, 2026
 *      Author: peterburton
 */

#ifndef INC_MAKE_DETECT_H_
#define INC_MAKE_DETECT_H_

#define IN_RIM_THRESHOLD 222 // max distance from the back of the rim to the center of the ball


typedef enum {
	SHOT_MISS = 0,
	SHOT_MAKE = 1,
	SHOT_NONE = 3
} ShotResult;


void Make_Detect_Init(void);
ShotResult Make_Detect_MadeShot(void);

#endif /* INC_MAKE_DETECT_H_ */
