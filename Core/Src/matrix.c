#include "ws2812.h"
#include "matrix.h"
#include "font_library.h"

// This function lights up each of the rows of the defined matrix individually for 1 second
void Matrix_Test(void)
{
	const uint8_t FONT_COUNT = 36;

	for (uint8_t i = 0; i < FONT_COUNT; i++)
	{
		Matrix_DrawGlyph(FONT[i], 0, 0, 5, 0, 0);

		WS2812_Show();
		HAL_Delay(500);

		WS2812_Clear();
	}
}


uint16_t Coordinate_to_Pixel(uint16_t x, uint16_t y)
{
	uint16_t pix_num;
	if(x < MATRIX_WIDTH && y < MATRIX_HEIGHT)
	{
		uint8_t even_row = y % 2;
		if(even_row == 0)
		{
			// even rows: left to right
			pix_num = (MATRIX_WIDTH * y) + x;
		}
		else
		{
			// odd rows: right to left
			pix_num = (MATRIX_WIDTH * y) + (MATRIX_WIDTH - 1 - x);
		}
	}
	else
	{
		// not valid
		/// figure out a good way to address this, for now clips to the max
		pix_num = LED_COUNT;
	}

	return pix_num;
}

void Matrix_Set_Pixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	uint16_t pix_num = Coordinate_to_Pixel(x, y);
	WS2812_SetPixel(pix_num, red, green, blue);
}

void Matrix_DrawGlyph(const uint8_t *glyph,
                      uint16_t start_x,
                      uint16_t start_y,
                      uint8_t red,
                      uint8_t green,
                      uint8_t blue)
{
    for (uint8_t row = 0; row < 7; row++)
    {
        for (uint8_t col = 0; col < 5; col++)
        {
            // Check if this pixel is lit
            if (glyph[row] & (1 << (4 - col)))
            {
                uint16_t x = start_x + col;
                uint16_t y = start_y + row;

                // Only draw pixels inside the matrix
                if (x < MATRIX_WIDTH && y < MATRIX_HEIGHT)
                {
                    uint16_t pix_num = Coordinate_to_Pixel(x, y);

                    WS2812_SetPixel(pix_num, red, green, blue);
                }
            }
        }
    }
}
