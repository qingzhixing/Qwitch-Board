#pragma once

#ifndef _OLED_H_
#define _OLED_H_
#include <U8g2lib.h>
#include <Arduino.h>

#define NORMAL_FONT u8g2_font_t0_13_tr
#define BOLD_FONT u8g2_font_t0_13b_tr

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

void oled_init();

#endif // !_OLED_H_