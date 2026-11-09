# Vortex Model M SSK KIT (ANSI 6.25u WK) — current vial-qmk port

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
| RGB | RGB Matrix, 92 × WS2812 (6028) on A7 (TIM3 CH2, DMA1 ch3), max brightness 255, the vendor's 43 effects |
| EEPROM | wear-leveling in the top 8 KB of flash (0x0801E000), the same region the vendor used |

### Matrix LED layout

<table>
  <thead>
    <tr><th>PINs</th><th></th><th>PC14</th><th>PC15</th><th>PA0</th><th>PA2</th><th>PA3</th><th>PB10</th><th>PB5</th><th>PB14</th><th>PB15</th><th>PB13</th><th>PB4</th><th>PB3</th><th>PA15</th><th>PB12</th><th>PB8</th><th>PB9</th><th>PB6</th><th>PB7</th></tr>
    <tr><th></th><th><i>row\col<i></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>10</th><th>11</th><th>12</th><th>13</th><th>14</th><th>15</th><th>16</th><th>17</th></tr>
  </thead>
  <tbody>
    <tr><th>PA1</th><th>0</th><td><kbd>Esc</kbd></td><td><kbd>F1</kbd></td><td><kbd>F2</kbd></td><td><kbd>F3</kbd></td><td><kbd>F4</kbd></td><td><kbd>F5</kbd></td><td><kbd>F6</kbd></td><td><kbd>F7</kbd></td><td><kbd>F8</kbd></td><td><kbd>F9</kbd></td><td><kbd>F10</kbd></td><td><kbd>F11</kbd></td><td><kbd>F12</kbd></td><td><kbd>Print<br>Screen</kbd></td><td><kbd>Scroll<br>Lock</kbd></td><td><kbd>Pause</kbd></td><td></td><td></td></tr>
    <tr><th>PA4</th><th>1</th><td><kbd>`</kbd></td><td><kbd>1</kbd></td><td><kbd>2</kbd></td><td><kbd>3</kbd></td><td><kbd>4</kbd></td><td><kbd>5</kbd></td><td><kbd>6</kbd></td><td><kbd>7</kbd></td><td><kbd>8</kbd></td><td><kbd>9</kbd></td><td><kbd>0</kbd></td><td><kbd>-</kbd></td><td><kbd>=</kbd></td><td></td><td><kbd>Backspace</kbd></td><td><kbd>Insert</kbd></td><td><kbd>Home</kbd></td><td><kbd>Page<br>Up</kbd></td></tr>
    <tr><th>PA5</th><th>2</th><td><kbd>Tab</kbd></td><td><kbd>Q</kbd></td><td><kbd>W</kbd></td><td><kbd>E</kbd></td><td><kbd>R</kbd></td><td><kbd>T</kbd></td><td><kbd>Y</kbd></td><td><kbd>U</kbd></td><td><kbd>I</kbd></td><td><kbd>O</kbd></td><td><kbd>P</kbd></td><td><kbd>[</kbd></td><td><kbd>]</kbd></td><td></td><td><kbd>\</kbd></td><td><kbd>Delete</kbd></td><td><kbd>End</kbd></td><td><kbd>Page<br>Down</kbd></td></tr>
    <tr><th>PB0</th><th>3</th><td><kbd>Caps<br>Lock</kbd></td><td><kbd>A</kbd></td><td><kbd>S</kbd></td><td><kbd>D</kbd></td><td><kbd>F</kbd></td><td><kbd>G</kbd></td><td><kbd>H</kbd></td><td><kbd>J</kbd></td><td><kbd>K</kbd></td><td><kbd>L</kbd></td><td><kbd>;</kbd></td><td><kbd>'</kbd></td><td><kbd>Enter</kbd></td><td></td><td></td><td><kbd> </kbd></td><td><kbd> </kbd></td><td><kbd> </kbd></td></tr>
    <tr><th>PA6</th><th>4</th><td><kbd>Shifl</kbd></td><td></td><td><kbd>Z</kbd></td><td><kbd>X</kbd></td><td><kbd>C</kbd></td><td><kbd>V</kbd></td><td><kbd>B</kbd></td><td><kbd>N</kbd></td><td><kbd>M</kbd></td><td><kbd>,</kbd></td><td><kbd>.</kbd></td><td><kbd>/</kbd></td><td><kbd>Shift</kbd></td><td></td><td></td><td><kbd> </kbd></td><td><kbd>Up</kbd></td><td><kbd> </kbd></td></tr>
    <tr><th>PC13</th><th>5</th><td><kbd>Ctrl</kbd></td><td><kbd>Gui</kbd></td><td><kbd>Alt</kbd></td><td></td><td></td><td></td><td><kbd>Space</kbd></td><td></td><td></td><td></td><td><kbd>Alt</kbd></td><td><kbd>Gui</kbd></td><td><kbd>Menu</kbd></td><td></td><td><kbd>Ctrl</kbd></td><td><kbd>Left</kbd></td><td><kbd>Down</kbd></td><td><kbd>Right</kbd></td></tr>
  </tbody>
</table>

> [!NOTE]
> There are 5 keys ([3,15], [3,16], [3,17], [4,15], [4,17]) which on PCB, but not accessible due to topcase overlap

### LED layout

The RGB LED strip has horizontal ZigZag (Serpentine) layout, starting from bottom right corner (`Right` key) up to top left corner (`Esc` key)

### Lock indicators

The RGB LED under **Caps Lock** and **Scroll Lock** turns blue while that lock is on (`model_m_us625.c`).
If `swap_control_capslock` enabled, RGB LED under **Ctrl** will be used as CapsLock indicator.
It's drawn on top of the running effect at the same brightness as the rest of the lighting, with a minimum level (`LOCK_MIN_LEVEL`) so it never disappears.
It also works with the RGB lighting switched off.
Then only the lock keys light up.

## Build & flash

```shell
    make vortex/model_m_us625:vial
    dfu-util -d 1EAF:0003 -a 2 -R -D vortex/model_m_us625_vial.bin
```

To get into the bootloader: Fn + Shift + Esc (QK_BOOT), or hold Esc while plugging in (bootmagic).

## Changes from the vendor firmware

* **Keycodes**: Vial protocol 6 / QMK ≥ 0.19 numbering. RGB keys are now `RM_*`. The old `RGB_*` names now control rgblight, not RGB Matrix.
* **Vial lighting**: VialRGB is used, so the Lighting tab shows the real RGB Matrix effect names.
  The vendor used the rgblight emulation, which mislabels them.
  To revert, set `VIALRGB_ENABLE = no` in `keymaps/vial/rules.mk` and `"lighting": "qmk_rgblight"` in `vial.json`.
* **vial.json**: the USB IDs match the device (`0xEB88/0x0024`).
* **WS2812 timing**: the bit period is now the standard 1.25 µs. The old QMK driver used 12.5 µs. The vendor's 350/800 ns high times are kept (`WS2812_T1H 800`).
* **App flash**: the linker script gives the firmware 112 KB, up from 56 KB, and keeps the EEPROM pages out of it.
* New QMK effects (Starlight, Riverflow, Flower Blooming, …) are available but left off. To use them, enable them in `keyboard.json` → `rgb_matrix.animations`.
* Saved settings are reset after flashing, because the EEPROM format differs from the vendor's.
