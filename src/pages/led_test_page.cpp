#include "pages/led_test_page.hpp"

#include <interaction.hpp>
#include <keyboard.hpp>
#include <oled.hpp>

PageDisplay led_test_page = PageDisplay("LED Test Page", led_test_page_function, led_test_page_init,
                                        icon_smile_bits);

void led_test_page_init() {
}

static void interaction_handler() {
	if (is_page_select_key_pressing())
		return;

	if (is_key_on_pressed(KEY_A)) {
		toggle_led();
	}
}

static void display_handler() {
	oled.clearBuffer();
	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(30, 12, "LED Test");
	oled.setDrawColor(1);

	if (is_led_on()) {
		oled.drawBox(5, 21, 128 - 6 * 2 - 1, 64 - 6 * 2 - 1 - 16);
		oled.setDrawColor(0);
		oled.drawStr(25, 41, "[A] LED ON");
		oled.setDrawColor(1);
	} else {
		oled.drawFrame(5, 21, 128 - 6 * 2 - 1, 64 - 6 * 2 - 1 - 16);
		oled.drawStr(25, 41, "[A] LED OFF");
	}
	oled.sendBuffer();
}

void led_test_page_function() {
	interaction_handler();
	display_handler();
}
