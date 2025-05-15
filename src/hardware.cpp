//
// Created by qingzhixing on 2025/5/15.
//

#include "hardware.hpp"
#include <keyboard.hpp>
#include <nvs_controller.hpp>

static bool initialized = false;

#define INIT_KEY_DATA(key_str) \
    do{\
        if (!prefs.isKey(key_str))\
            prefs.putShort(key_str, 0);\
    }while(0)

static void hw_data_init() {
    INIT_KEY_DATA("keypress_UP");
    INIT_KEY_DATA("keypress_DOWN");
    INIT_KEY_DATA("keypress_LEFT");
    INIT_KEY_DATA("keypress_RIGHT");
    INIT_KEY_DATA("keypress_A");
    INIT_KEY_DATA("keypress_B");
}

void hardware_record() {
    prefs.begin(NVS_NAMESPACE, false);
    if (!initialized) {
        initialized = true;
        hw_data_init();
    }
    if (is_key_on_pressed(KEY_UP)) {
        const short key_cnt = prefs.getShort("keypress_UP");
        prefs.putShort("keypress_UP", key_cnt + 1);
    }

    if (is_key_on_pressed(KEY_DOWN)) {
        const short key_cnt = prefs.getShort("keypress_DOWN");
        prefs.putShort("keypress_DOWN", key_cnt + 1);
    }

    if (is_key_on_pressed(KEY_LEFT)) {
        const short key_cnt = prefs.getShort("keypress_LEFT");
        prefs.putShort("keypress_LEFT", key_cnt + 1);
    }

    if (is_key_on_pressed(KEY_RIGHT)) {
        const short key_cnt = prefs.getShort("keypress_RIGHT");
        prefs.putShort("keypress_RIGHT", key_cnt + 1);
    }

    if (is_key_on_pressed(KEY_A)) {
        const short key_cnt = prefs.getShort("keypress_A");
        prefs.putShort("keypress_A", key_cnt + 1);
    }

    if (is_key_on_pressed(KEY_B)) {
        const short key_cnt = prefs.getShort("keypress_B");
        prefs.putShort("keypress_B", key_cnt + 1);
    }

    // 同步nvs
    prefs.end();
}
