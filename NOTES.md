# QMK Build Notes for Boardsource Lily58

## Hardware
- Boardsource Lily58 (not Lulu - different board!)
- BLOK RP2040 controllers
- 70 LEDs (35 per half: 29 per-key + 6 underglow)
- OLED displays

## Working Configuration

### qmk.json
```json
{
    "userspace_version": "1.0",
    "build_targets": [
        ["lily58/rev1", "supercoolalan"]
    ]
}
```

### rules.mk
```makefile
CONVERT_TO = blok

# OLED
OLED_ENABLE = yes

# RGB Lighting
RGBLIGHT_ENABLE = yes
```

## Key Findings

### 1. Keyboard Target
- Use `lily58/rev1` with `CONVERT_TO = blok`
- Do NOT use `boardsource/lulu/rp2040` - that's a different keyboard

### 2. BLOK Converter
- The converter handles pin remapping automatically (D3 -> GP29 for RGB, etc.)
- Do NOT manually define pins in config.h - it will conflict with the converter

### 3. RGBLIGHT vs RGB_MATRIX
- RGBLIGHT is simpler and works out of the box
- RGB_MATRIX requires defining `g_led_config` with LED positions
- lily58/rev1 has RGBLIGHT configured with 12 LEDs by default

### 4. LED Count Override Issue
- Default lily58 has 12 LEDs, we have 70
- `#undef RGBLIGHT_LED_COUNT` in config.h causes build errors (known bug)
- OPT_DEFS approach also failed
- May need to work around this differently

### 5. Keycode Changes (QMK 2024+)
- Old RGB keycodes (RGB_TOG, RGB_MOD, etc.) are deprecated
- New keycodes use `UG_` prefix (underglow):
  - `UG_TOGG` - toggle
  - `UG_NEXT` / `UG_PREV` - cycle modes
  - `UG_SATU` / `UG_SATD` - saturation
  - `UG_VALU` / `UG_VALD` - brightness/value
  - `UG_HUEU` / `UG_HUED` - hue

### 6. OLED
- Works with just `OLED_ENABLE = yes`
- Converter handles I2C pin remapping

## What Didn't Work
- Setting `WS2812_DI_PIN` in config.h (conflicts with converter)
- Setting I2C pins manually in config.h
- Using `#undef RGBLIGHT_LED_COUNT` in config.h
- Using `OPT_DEFS += -DRGBLIGHT_LED_COUNT=70` in rules.mk
- Old RGB_ keycodes (RGB_TOG, RGB_MOD, etc.)

## OLED Configuration (WORKING)
- BLOK uses **GP16/GP17** for I2C (not GP22/GP23)
- Config needed in config.h:
```c
#define I2C_DRIVER I2CD0
#define I2C0_SDA_PIN GP16
#define I2C0_SCL_PIN GP17
```
- Need `oled_task_user()` function in keymap.c to display content after splash

## TODO
- Figure out how to increase LED count from 12 to 70
