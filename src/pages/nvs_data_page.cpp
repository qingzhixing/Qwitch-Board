//
// Created by qingzhixing on 2025/5/15.
//

#include "pages/nvs_data_page.hpp"
#include <nvs_controller.hpp>
#include <oled.hpp>

PageDisplay nvs_data_page = PageDisplay("NVS Data", nvs_data_page_function, nvs_data_page_init, icon_camera_bits);

static short reboot_time = 0;
static short keypress_UP = 0;
static short keypress_DOWN = 0;
static short keypress_LEFT = 0;
static short keypress_RIGHT = 0;
static short keypress_A = 0;
static short keypress_B = 0;

#define GET_SYNC_KEY(key) \
    key = prefs.getShort(#key, 0)

void nvs_data_page_init() {
}

static void synchronous_data() {
    prefs.begin(NVS_NAMESPACE, true);
    GET_SYNC_KEY(reboot_time);
    GET_SYNC_KEY(keypress_UP);
    GET_SYNC_KEY(keypress_DOWN);
    GET_SYNC_KEY(keypress_LEFT);
    GET_SYNC_KEY(keypress_RIGHT);
    GET_SYNC_KEY(keypress_A);
    GET_SYNC_KEY(keypress_B);
    prefs.end();
}

static void display_data() {
    oled.clearBuffer();
    oled.setFont(TEXT_NORMAL_FONT);
    oled.drawBox(0, 0, 128, 16);
    oled.setDrawColor(0);
    oled.drawStr(30, 12, "NVS Data");
    oled.setDrawColor(1);

    char buffer[64];
    sprintf(buffer, "Reboot: %d", reboot_time);
    oled.drawStr(5, 26, buffer);

    sprintf(buffer, "Keypress A: %d", keypress_A);
    oled.drawStr(5, 36, buffer);

    sprintf(buffer, "Keypress B: %d", keypress_B);
    oled.drawStr(5, 46, buffer);

    oled.sendBuffer();
}

void nvs_data_page_function() {
    synchronous_data();
    display_data();
}
