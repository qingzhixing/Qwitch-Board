#include "pages/old_menu.hpp"
#include "page_controller.hpp"
#include <oled.hpp>
#include <Arduino.h>
#include <keyboard.hpp>
#include <interaction.hpp>

PageDisplay old_menu = PageDisplay("Old Menu", menu_page_function, menu_page_initialize, icon_oled_bits);

#define PAGE_AMOUNT (int(page_displays.size()))

// 连续交互间隔
static Interaction interaction(200);
static int current_page = 0;
static bool hide_info = true;
static bool need_update_select_screen = false;

void display_page_select_info() {
	oled.clearBuffer();

	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(30, 12, "Select Tips");
	oled.setDrawColor(1);

	oled.drawStr(5, 31, "Press A to select ");
	oled.drawStr(5, 47, "Hold L/R to switch");
	oled.drawStr(5, 63, "Press B to on/off tips");

	oled.sendBuffer();
	hide_info = false;
}

void menu_page_initialize() {
	interaction.update_interaction_tick();

	// 冷却500ms
	interaction.add_cooldown(300);

	need_update_select_screen = true;
}

void menu_page_function() {
	if (page_displays.empty()) {
		oled.clearBuffer();
		oled.drawStr(30, 10, "!!ERROR!!");
		oled.drawStr(5, 31, "No registered page!");
		oled.sendBuffer();
		return;
	}

	if (is_key_on_pressed(KEY_B)) {
		hide_info = !hide_info;
		if (!hide_info) {
			display_page_select_info();
		} else {
			oled.clearBuffer();
			oled.sendBuffer();

			need_update_select_screen = true;
		}
	}

	if (is_key_pressing(KEY_LEFT) && interaction.can_interact() && hide_info) {
		interaction.update_interaction_tick();
		need_update_select_screen = true;
		current_page = (current_page - 1 + PAGE_AMOUNT) % PAGE_AMOUNT;
	}
	if (is_key_pressing(KEY_RIGHT) && interaction.can_interact()) {
		interaction.update_interaction_tick();
		need_update_select_screen = true;
		current_page = (current_page + 1) % PAGE_AMOUNT;
	}

	if (is_key_on_pressed(KEY_A) && hide_info) {
		interaction.update_interaction_tick();
		auto &page_display = page_displays[current_page];
		set_display_function(page_display);
	}

	if (need_update_select_screen && hide_info) {
		char display_str[32] = {};
		auto &page_display = page_displays[current_page];
		snprintf(display_str, sizeof(display_str), "@[%s]", page_display.page_name);

		oled.clearBuffer();
		oled.drawBox(0, 21, 128, 16);
		oled.setDrawColor(0);
		oled.drawStr(10, 33, display_str);
		oled.setDrawColor(1);

		oled.drawStr(15, 47, "Press A to enter");
		oled.drawStr(15, 63, "Press B to tips");
		oled.sendBuffer();
	}
}
