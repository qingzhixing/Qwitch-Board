#include "page_controller/new_menu.hpp"
#include <oled.hpp>
#include <bitmaps.hpp>

PageDisplay new_menu = PageDisplay("New Menu", new_menu_function, new_menu_initialize, epd_bitmap_icon_oled);


void new_menu_initialize()
{
	oled.clearBuffer();
	// backgrounds
	oled.drawBitmap(0, 0, 128 / 8, 20, bitmap_item_backgrounds[0]);	 // keyboard
	oled.drawBitmap(0, 22, 128 / 8, 20, bitmap_item_backgrounds[1]); // oled
	oled.drawBitmap(0, 44, 128 / 8, 20, bitmap_item_backgrounds[0]); // home
	// icons
	oled.drawBitmap(4, 2, 16 / 8, 16, bitmap_icons[0]);
	oled.drawBitmap(4, 24, 16 / 8, 16, bitmap_icons[1]);
	oled.drawBitmap(4, 46, 16 / 8, 16, bitmap_icons[2]);
	// text
	oled.setFont(NORMAL_FONT);
	oled.drawStr(24, 15, "Keyboard Test");
	oled.setFont(BOLD_FONT);
	oled.drawStr(24, 37, "OLED Test");
	oled.setFont(NORMAL_FONT);
	oled.drawStr(24, 58, "Home Page");
	oled.sendBuffer();
}

void new_menu_function()
{
}
