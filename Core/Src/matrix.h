#ifndef MATRIX_H
#define MATRIX_H

#include "main.h"

#define MATRIX_WIDTH 22
#define MATRIX_HEIGHT 9


void Matrix_Test(void);
void Matrix_Set_Pixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);
void Matrix_DrawGlyph(const uint8_t *glyph,
                      uint16_t start_x,
                      uint16_t start_y,
                      uint8_t red,
                      uint8_t green,
                      uint8_t blue);
#endif
