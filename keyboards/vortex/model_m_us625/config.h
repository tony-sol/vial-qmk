// Model M-us625 (Vortex) — ported from vendor firmware "Model M_Solderable_vial.bin"
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/* WS2812 on A7 = TIM3_CH2, update-event DMA on DMA1 channel 3 */
#define WS2812_PWM_DRIVER  PWMD3
#define WS2812_PWM_CHANNEL 2
#define WS2812_DMA_STREAM  STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3
/* Vendor firmware used a 800 ns "1" pulse (current QMK default is 900 ns) */
#define WS2812_T1H 800

/* EEPROM emulation: last 8 KB of the 128 KB flash (0x0801E000), as in the vendor firmware.
 * Forced to 128 KB so it is placed correctly even if the flash-size register reads 64 KB. */
#define WEAR_LEVELING_EFL_FLASH_SIZE (128 * 1024)
#define WEAR_LEVELING_BACKING_SIZE 8192
