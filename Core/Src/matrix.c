#include "ws2812.h"
#include "matrix.h"
#include "font_library.h"

void Matrix_Set_Pixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);
void Matrix_DrawGlyph(const uint8_t *glyph, uint16_t start_x, uint16_t start_y, uint8_t red, uint8_t green, uint8_t blue);
void Matrix_Draw_Character(char character, int16_t start_x, uint8_t red, uint8_t green, uint8_t blue);
void Matrix_Draw_String(const char *string, int16_t start_x, uint8_t red, uint8_t green, uint8_t blue);

/// name: Matrix_Test
/// inputs: none
/// function: test function for module
/// return: none
void Matrix_Test(void)
{
//  // RED GREEN BLUE DISPLAY
//	Matrix_Draw_String("RED", 0, 100, 0, 0);
//	WS2812_Show();
//	HAL_Delay(1000);
//	WS2812_Clear();
//
//	Matrix_Draw_String("GRN", 0, 0, 100, 0);
//	WS2812_Show();
//	HAL_Delay(1000);
//	WS2812_Clear();
//
//	Matrix_Draw_String("BLU", 0, 0, 0, 100);
//	WS2812_Show();
//	HAL_Delay(1000);
//	WS2812_Clear();

	Matrix_Write_String("HELLO", 50, 0, 0);
}

/// name: Coordinate_to_Pixel
/// inputs: x coordinate, y coordinate
/// function: converts (x,y) coordinate to LED buffer index
/// return: pixel index number
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

/// name: Matrix_Set_Pixel
/// inputs: x coordinate, y coordinate, RGB value
/// function: sets the pixel at an (x,y) coordinate to a given RGB value
/// return: none
void Matrix_Set_Pixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	uint16_t pix_num = Coordinate_to_Pixel(x, y); // get the pixel index
	WS2812_SetPixel(pix_num, red, green, blue); // set that pixel index to the RGB value
}

/// name: Matrix_DrawGlyph
/// inputs: glyph, x coordinate, y coordinate, RGB value
/// function: sets pixels to a given RGB value at a given (x,y) location in a given glyph pattern
/// return: none
void Matrix_DrawGlyph(const uint8_t *glyph, uint16_t start_x, uint16_t start_y, uint8_t red, uint8_t green, uint8_t blue)
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

/// name: Matrix_Draw_Character
/// inputs: character, x offset, RGB value
/// function: draws the glyph corresponding to a given character at a given x offset in a given RGB value
/// return: none
void Matrix_Draw_Character(char character, int16_t start_x, uint8_t red, uint8_t green, uint8_t blue)
{
	const uint8_t *glyph = NULL;

	// look up the defined glyph in the 5x7 font for the given character
	for (int i = 0; i < (sizeof(FONT_5x7) / sizeof(FONT_5x7[0])); i++)
	{
		if(FONT_5x7[i].character == character)
		{
			glyph = FONT_5x7[i].glyph;
		}
	}
	// only draw if a valid glyph was found
	if(glyph != NULL)
	{
		Matrix_DrawGlyph(glyph, start_x, 1, red, green, blue);
	}
}

/// name: Matrix_Calculate_String_Width
/// inputs: string
/// function: calculates the width a string will take up in pixels
/// return: width in pixels
uint16_t Matrix_Calculate_String_Width(const char *string)
{
    uint16_t width = 0;
    uint16_t i = 0;

    for (i = 0; string[i] != '\0'; i++)
    {
        // Count characters
    }

    // 5 pixels per character + 1 pixel spacing
    // Remove spacing after the final character
    if (i > 0)
    {
        width = (i * 6) - 1;
    }

    return width;
}

/// name: Matrix_Draw_String
/// inputs: string, x offset, RGB value
/// function: draws each character in a given string
/// return: none
void Matrix_Draw_String(const char *string, int16_t start_x, uint8_t red, uint8_t green, uint8_t blue)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        Matrix_Draw_Character(string[i], (i * 6) + start_x, red, green, blue);
    }
}

/// name: Matrix_Write_String
/// inputs: string, RGB value
/// function: user function to write a string to the LED matrix, employing scrolling for longer strings
/// return: none
void Matrix_Write_String(const char *string, uint8_t red, uint8_t green, uint8_t blue)
{
	uint16_t width = Matrix_Calculate_String_Width(string);

	// for strings wider than the display they are displayed offset to the right and scroll to the left
	if(width > MATRIX_WIDTH)
	{
		// scroll double the width of the entire string to show everything
		int16_t overflow = width;
		for(int16_t scroll = overflow; scroll > (-overflow); scroll--)
		{
			WS2812_Clear();
			Matrix_Draw_String(string, scroll, red, green, blue);
			WS2812_Show();
			HAL_Delay(60); // show frame for at least 60ms
		}

	}
	else
	{
		WS2812_Clear();
		Matrix_Draw_String(string, 0, red, green, blue);
		WS2812_Show();
	}
}
