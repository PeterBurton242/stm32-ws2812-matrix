# STM32 WS2812 Matrix

I developed a driver to output to an LED matrix comprised of WS2812 LEDs using PWM and Timers. 

## Overview
The driver receives information about LED location and Color, then converts and transmits that data to the LED array. This allows for various designs and characters to be displayed according to the matrix dimensions.

## Components
- STM32L4
- WS2812 LEDs
- 5V power source

## Implementation
A PWM signal representing the color value is generated for each LED. Those signals are passed down the array/matrix applying the the color value to the designated LED. This functionality is expanded to create various displays on the LEDs themselves by mapping color values to LED locations.

## Methods
- PWM
- Timers
- Buffering

## Results / Features
- Full RGB spectrum support
- Driver supports array up to 255 x 255
- Modeler Code allows for diverse use-cases
