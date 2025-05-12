#include "oled.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, SCL, SDA);

void oled_init() {
	oled.begin();
	oled.clearBuffer();
	oled.setFont(TEXT_NORMAL_FONT);
	oled.setDrawColor(1);
	oled.setBitmapMode(1);
}
