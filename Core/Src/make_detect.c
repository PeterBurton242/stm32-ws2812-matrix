#include "make_detect.h"
#include "vl53l1x.h"
#include "vl53l1_platform.h"
#include "VL53L1X_api.h"
#include "matrix.h"
#include <stdio.h>


void MakeDetectInit(void){
	  uint8_t boot_state = 0;

	  int8_t boot_status = 0;
	  int8_t init_status = -1;

	  boot_status = VL53L1X_BootState(0x52, &boot_state);

	  if (boot_status == 0 && (boot_state & 0x01))
	  {
	      init_status = VL53L1X_SensorInit(0x52);
	  }

	  int8_t mode_status = -1;
	  int8_t timing_status = -1;
	  int8_t period_status = -1;

	  if (init_status == 0)
	  {
	      mode_status = VL53L1X_SetDistanceMode(0x52, 1);

	      if (mode_status == 0)
	      {
	          timing_status = VL53L1X_SetTimingBudgetInMs(0x52, 20);
	      }

	      if (timing_status == 0)
	      {
	          period_status = VL53L1X_SetInterMeasurementInMs(0x52, 25);
	      }

	      if (period_status == 0)
	      {
	    	  VL53L1X_StartRanging(0x52);
	      }
	  }
}

int MakeDetect_MadeShot(void){
	uint8_t range_status = 0;
	uint16_t distance_mm = 0;
	int8_t read_status = 0;
	uint8_t data_ready = 0;
	/* wait for next sample to be ready */
	  read_status = VL53L1X_CheckForDataReady(0x52, (uint8_t *)&data_ready);

	  if (read_status == 0 && data_ready)
	  {
		  read_status = VL53L1X_GetRangeStatus(
			  0x52, (uint8_t *)&range_status
		  );

		  if (read_status == 0)
		  {
			  read_status = VL53L1X_GetDistance(
				  0x52, (uint16_t *)&distance_mm
			  );
			  char dist_str[6];
			  snprintf(dist_str, sizeof(dist_str), "%d", distance_mm);
			  if(distance_mm < IN_RIM_THRESHOLD){
				  Matrix_Write_String(dist_str, 0, 50, 0); // green means make
			  }
			  else{
				  Matrix_Write_String(dist_str, 50, 0, 0); // red means not
			  }

			  HAL_Delay(100);
		  }

		  if (read_status == 0)
		  {
			  read_status = VL53L1X_ClearInterrupt(0x52);
		  }
	  }
}




