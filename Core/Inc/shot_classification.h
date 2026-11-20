/*
 * shot_classification.h
 *
 *  Created on: Nov 19, 2026
 *      Author: Peter
 */

#ifndef INC_SHOT_CLASSIFICATION_H_
#define INC_SHOT_CLASSIFICATION_H_

#define SHOT_COOLDOWN_MS 400U
typedef enum{
	SHOT_MISS = 0,
	SHOT_MAKE = 1,
	SHOT_NONE = 3
} ShotResult;


ShotResult Shot_Classification_Update(void);
#endif /* INC_SHOT_CLASSIFICATION_H_ */
