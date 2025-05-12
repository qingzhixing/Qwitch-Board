#pragma once

#ifndef OLED_H_
#define OLED_H_
#include <U8g2lib.h>

#define MENU_NORMAL_FONT u8g2_font_t0_13_tr
#define MENU_BOLD_FONT u8g2_font_t0_13b_tr
#define TEXT_NORMAL_FONT u8g2_font_ncenB08_tr

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;

void oled_init();

#endif // OLED_H_
