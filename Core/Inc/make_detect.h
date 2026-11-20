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
	MAKE_NO = 0,
	MAKE_YES = 1,
	MAKE_UNDEF = 2
} MakeResult;


void Make_Detect_Init(void);
MakeResult Make_Detection(void);

#endif /* INC_MAKE_DETECT_H_ */
