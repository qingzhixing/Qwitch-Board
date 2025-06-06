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
    oled.drawBox(0, 0, 128, 12);
    oled.setDrawColor(0);
    oled.drawStr(30, 10, "NVS Data");
    oled.setDrawColor(1);

    oled.drawStr(5, 22, String("Reboot: "+String(reboot_time)).c_str());

    oled.drawStr(5, 32, "Keypress: ");
    oled.drawStr(5, 44, String("U: "+String(keypress_UP)).c_str());
    oled.drawStr(64, 44, String("D: "+String(keypress_DOWN)).c_str());
    oled.drawStr(5, 54, String("L: "+String(keypress_LEFT)).c_str());
    oled.drawStr(64, 54, String("R: "+String(keypress_RIGHT)).c_str());
    oled.drawStr(5, 64, String("A: "+String(keypress_A)).c_str());
    oled.drawStr(64, 64, String("B: "+String(keypress_B)).c_str());
    oled.sendBuffer();
}

void nvs_data_page_function() {
    synchronous_data();
    display_data();
}
