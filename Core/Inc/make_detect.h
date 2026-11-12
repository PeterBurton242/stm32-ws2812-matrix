/*
 * make_detect.h
 *
 *  Created on: Nov 10, 2026
 *      Author: peterburton
 */

#ifndef INC_MAKE_DETECT_H_
#define INC_MAKE_DETECT_H_

#define IN_RIM_THRESHOLD 222 // max distance from the back of the rim to the center of the ball



void MakeDetectInit(void);
int MakeDetect_MadeShot(void);

#endif /* INC_MAKE_DETECT_H_ */
