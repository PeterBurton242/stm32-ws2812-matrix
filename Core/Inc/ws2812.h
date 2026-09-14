#ifndef WS2812_H
#define WS2812_H

#include "main.h"

#define LED_COUNT 198

void WS2812_SetPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
void WS2812_Show(void);
void WS2812_Clear(void);
#endif
