#include "oled.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* clock=*/SCL, /* data=*/SDA);

void oled_init()
{
	oled.begin();
	oled.clearBuffer();
	oled.setFont(u8g2_font_ncenB08_tr);
	oled.setDrawColor(1);
}