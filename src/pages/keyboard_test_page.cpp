#include "pages/keyboard_test_page.hpp"

#include <Arduino.h>
#include <bitmaps.hpp>
#include <keyboard.hpp>
#include <oled.hpp>

PageDisplay keyboard_test_page =
    PageDisplay("Kbd Test Page", keyboard_test_page_update, keyboard_test_page_initialize, icon_keyboard_bits);

void keyboard_test_page_initialize() {}

void keyboard_test_page_update()
{
    oled.clearBuffer();
    oled.drawBox(0, 0, 128, 16);
    oled.setDrawColor(0);
    oled.drawStr(20, 12, "Keyboard Test");
    oled.setDrawColor(1);

    // 画圆表示按键状态
    // Up Down Left Right
    if (is_key_pressing(KEY_UP))
    {
        oled.drawDisc(31, 28, 5);
    }
    else
    {
        oled.drawCircle(31, 28, 5);
    }

    if (is_key_pressing(KEY_DOWN))
    {
        oled.drawDisc(31, 50, 5);
    }
    else
    {
        oled.drawCircle(31, 50, 5);
    }

    if (is_key_pressing(KEY_LEFT))
    {
        oled.drawDisc(20, 39, 5);
    }
    else
    {
        oled.drawCircle(20, 39, 5);
    }

    if (is_key_pressing(KEY_RIGHT))
    {
        oled.drawDisc(42, 39, 5);
    }
    else
    {
        oled.drawCircle(42, 39, 5);
    }

    // A B
    if (is_key_pressing(KEY_A))
    {
        oled.drawDisc(90, 30, 5);
    }
    else
    {
        oled.drawCircle(90, 30, 5);
    }

    if (is_key_pressing(KEY_B))
    {
        oled.drawDisc(105, 42, 5);
    }
    else
    {
        oled.drawCircle(105, 42, 5);
    }

    oled.sendBuffer();
}

void KeyboardTestPage::update() { keyboard_test_page_update(); }
void KeyboardTestPage::initialize() { keyboard_test_page_initialize(); }
