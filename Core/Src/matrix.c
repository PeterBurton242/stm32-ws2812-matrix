#include "ws2812.h"
#include "matrix.h"


// This function lights up each of the rows of the defined matrix individually for 1 second
void Matrix_Test(void)
{
    for (uint8_t i = 0; i < MATRIX_HIGHT; i++)
    {
  	  for(uint8_t j = 0; j < MATRIX_WIDTH; j++)
  	  {
  		  uint8_t pix = (i * MATRIX_WIDTH) + j;
  		  WS2812_SetPixel(pix, 50, 0, 0);
  	  }

  	  WS2812_Show();
  	  HAL_Delay(1000);
  	  WS2812_Clear();
    }
}


uint16_t Coordinate_to_Pixel(uint16_t x, uint16_t y)
{
	uint16_t pix_num;
	if(x <= MATRIX_WIDTH && y <= MATRIX_HIGHT)
	{
		uint8_t even_row = y % 2;
		if(even_row == 0)
		{
			pix_num = (MATRIX_WIDTH * y) + x;
		}
		else
		{
			pix_num = (MATRIX_WIDTH * y) + ((MATRIX_WIDTH - 1) - x);
		}
	}
	else
	{
		// not valid
		/// figure out a good way to address this, for now just 0
		pix_num = 0;
	}

	return pix_num;
}
