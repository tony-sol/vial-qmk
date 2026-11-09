// SPDX-License-Identifier: GPL-2.0-or-later
// The vendor board runs the STM32F103 from a 16 MHz crystal:
// RCC_CFGR = PLLSRC=HSE, PLLXTPRE=/2, PLLMUL=x9 -> 72 MHz.
#pragma once
#include_next <mcuconf.h>

#undef  STM32_HSECLK
#define STM32_HSECLK 16000000U
#undef  STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2

/* WS2812 PWM driver */
#undef  STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef  STM32_FLASH_SECTORS_PER_BANK
#define STM32_FLASH_SECTORS_PER_BANK 128
