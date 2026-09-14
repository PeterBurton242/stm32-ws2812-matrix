#include "ws2812.h"
#include "tim.h"

#define PWM_0 30
#define PWM_1 60

#define RESET_SLOTS 50
#define PWM_BUFFER_SIZE (LED_COUNT * 24 + RESET_SLOTS)

uint16_t pwm_buffer[PWM_BUFFER_SIZE];

void WS2812_SetPixel(uint16_t index,
                     uint8_t r,
                     uint8_t g,
                     uint8_t b)
{
    if (index >= LED_COUNT)
        return;

    /*
     * WS2812 transmits:
     * G7 ... G0
     * R7 ... R0
     * B7 ... B0
     */
    uint32_t color =
        ((uint32_t)g << 16) |
        ((uint32_t)r << 8)  |
        ((uint32_t)b);

    for (int i = 0; i < 24; i++)
    {
        if (color & (1UL << (23 - i)))
        {
            pwm_buffer[index * 24 + i] = PWM_1;
        }
        else
        {
            pwm_buffer[index * 24 + i] = PWM_0;
        }
    }
}

void WS2812_Show(void)
{
    HAL_TIM_PWM_Start_DMA(
        &htim1,
        TIM_CHANNEL_1,
        (uint32_t *)pwm_buffer,
        PWM_BUFFER_SIZE
    );

    while (HAL_DMA_GetState(
        htim1.hdma[TIM_DMA_ID_CC1]) != HAL_DMA_STATE_READY)
    {
    }

    /*
     * Reset slots already provide ~62.5 us LOW.
     * Give the transfer additional time to settle before stopping.
     */
    HAL_Delay(1);

    HAL_TIM_PWM_Stop_DMA(
        &htim1,
        TIM_CHANNEL_1
    );
}

void WS2812_Clear(void)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
        WS2812_SetPixel(i, 0, 0, 0);
    }

    // Reset/latch portion must actually be LOW
    for (int i = LED_COUNT * 24;
         i < LED_COUNT * 24 + 50;
         i++)
    {
        pwm_buffer[i] = 0;
    }
}

