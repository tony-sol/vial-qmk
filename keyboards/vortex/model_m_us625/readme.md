# Model M ISO 6.25 (Vortex) — current vial-qmk port

> [!IMPORTANT]
> Special thanks to @henryk-zaborowski who made [a first rebuilt](https://github.com/henryk-zaborowski/vial-qmk/tree/vortex_model_m_ssk/keyboards/vortex_model_m_h)

A port to current vial-qmk (tested against `vial` @ `dd43959ae5`) of a definition rebuilt from the vendor binary
`Model M_Solderable_vial.bin`.

## Hardware

| Item | Value |
|---|---|
| MCU | STM32F103xB (128 KB flash, 20 KB RAM), **16 MHz crystal** (HSE/2 × 9 = 72 MHz) |
| Bootloader | stm32duino / Maple, app at 0x08002000, DFU 1EAF:0003 |
| USB | VID `0xEB88`, PID `0x0024`, "Vortex" / "Model M us6.25" |
| Matrix | 6 × 18, ROW2COL. Rows A1 A4 A5 B0 A6 C13. Cols C14 C15 A0 A2 A3 B10 B5 B14 B15 B13 B4 B3 A15 B12 B8 B9 B6 B7 |
| Caps Lock LED | B1, active low |
| RGB | RGB Matrix, 92 × WS2812 (6028) on A7 (TIM3 CH2, DMA1 ch3), max brightness 200, the vendor's 43 effects |
| EEPROM | wear-leveling in the top 8 KB of flash (0x0801E000), the same region the vendor used |

## Lock indicators

The RGB LED under **Caps Lock** and **Scroll Lock** turns blue while that lock is on (`vortex_model_m_us625.c`).
It's drawn on top of the running effect at the same brightness as the rest of the lighting, with a minimum level (`LOCK_MIN_LEVEL`) so it never disappears. It also works with the RGB lighting switched off. Then only the lock keys light up.

## Build & flash

    make vortex/model_m_us625:vial
    dfu-util -d 1EAF:0003 -a 2 -R -D vortex/model_m_us625_vial.bin

To get into the bootloader: Fn + Esc (QK_BOOT), or hold Esc while plugging in (bootmagic).

## Changes from the vendor firmware

* **Keycodes**: Vial protocol 6 / QMK ≥ 0.19 numbering. RGB keys are now `RM_*`. The old `RGB_*` names
  now control rgblight, not RGB Matrix.
* **Vial lighting**: VialRGB is used, so the Lighting tab shows the real RGB Matrix effect names. The vendor
  used the rgblight emulation, which mislabels them. To revert, set `VIALRGB_ENABLE = no` in
  `keymaps/vial/rules.mk` and `"lighting": "qmk_rgblight"` in `vial.json`.
* **vial.json**: the USB IDs match the device (`0xEB88/0x0024`).
* **WS2812 timing**: the bit period is now the standard 1.25 µs. The old QMK driver used 12.5 µs.
  The vendor's 350/800 ns high times are kept (`WS2812_T1H 800`).
* **LED map**: matrix [0][16]/[0][17] (no switch there) are now `NO_LED`, not LED 0.
* **App flash**: the linker script gives the firmware 112 KB, up from 56 KB, and keeps the EEPROM pages out of it.
* New QMK effects (Starlight, Riverflow, Flower Blooming, …) are available but left off. To use them, enable
  them in `keyboard.json` → `rgb_matrix.animations`.
* Saved settings are reset after flashing, because the EEPROM format differs from the vendor's.
