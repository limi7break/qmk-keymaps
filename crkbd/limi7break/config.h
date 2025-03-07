#pragma once

#define MASTER_RIGHT
#define LAYER_STATE_8BIT
#define NO_ACTION_ONESHOT

#ifdef COMBO_ENABLE
    #define COMBO_TERM 40
#endif // COMBO_ENABLE

#ifdef OLED_ENABLE
    #define OLED_TIMEOUT 0
#endif // OLED_ENABLE

#ifdef POINTING_DEVICE_ENABLE
    #define SPLIT_POINTING_ENABLE
    #define POINTING_DEVICE_RIGHT
    #define CIRQUE_PINNACLE_DIAMETER_MM 40
    #define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
    #define CIRQUE_PINNACLE_TAP_ENABLE
#endif // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    // #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_LIMI7BREAK
    #define RGB_MATRIX_DEFAULT_SAT 255
    #define RGB_MATRIX_DEFAULT_VAL 64
    #define RGB_MATRIX_DEFAULT_SPD 64
    #define ENABLE_RGB_MATRIX_CUSTOM_LIMI7BREAK
#endif // RGB_MATRIX_ENABLE
