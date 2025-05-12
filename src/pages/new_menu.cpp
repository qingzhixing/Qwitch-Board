#include "pages/new_menu.hpp"
#include "page_controller.hpp"
#include <oled.hpp>
#include <bitmaps.hpp>
#include <interaction.hpp>
#include <keyboard.hpp>

PageDisplay new_menu = PageDisplay("New Menu", new_menu_function, new_menu_initialize, icon_oled_bits);

// 连续交互间隔
static Interaction interaction(200);

static int current_page_index = 0;

void new_menu_initialize() {
	interaction.update_interaction_tick();
	interaction.add_cooldown(300);
	oled.clearBuffer();
}

static void interaction_handler() {
	if (is_key_on_pressed(KEY_A)) {
		set_display_function(page_displays[current_page_index]);
		interaction.update_interaction_tick();
		return;
	}

	const auto page_amount = static_cast<int>(page_displays.size());
	if (is_key_on_pressed(KEY_UP) || (is_key_pressing(KEY_UP) && interaction.can_interact())) {
		current_page_index = (current_page_index - 1 + page_amount) % page_amount;
		interaction.update_interaction_tick();
		return;
	}

	if (is_key_on_pressed(KEY_DOWN) || (is_key_pressing(KEY_DOWN) && interaction.can_interact())) {
		current_page_index = (current_page_index + 1) % page_amount;
		interaction.update_interaction_tick();
		return;
	}
}

static void display_menu() {
	const auto page_amount = static_cast<int>(page_displays.size());

	const PageDisplay *current_page = nullptr;

	oled.clearBuffer();

	// draw first
	current_page = &page_displays[(current_page_index - 1 + page_amount) % page_amount];
	oled.drawXBM(4, 2, 16, 16, current_page->page_icon);
	oled.drawXBM(0, 0, 128, 20, background_normal_bits);
	oled.setFont(MENU_NORMAL_FONT);
	oled.drawStr(24, 15, current_page->page_name);

	// second page
	current_page = &page_displays[current_page_index];
	oled.drawXBM(4, 24, 16, 16, current_page->page_icon);
	oled.drawXBM(0, 22, 128, 20, background_center_bits);
	oled.setFont(MENU_BOLD_FONT);
	oled.drawStr(24, 37, current_page->page_name);

	// third page
	current_page = &page_displays[(current_page_index + 1) % page_amount];
	oled.drawXBM(4, 46, 16, 16, current_page->page_icon);
	oled.drawXBM(0, 44, 128, 20, background_normal_bits);
	oled.setFont(MENU_NORMAL_FONT);
	oled.drawStr(24, 58, current_page->page_name);

	oled.setFont(TEXT_NORMAL_FONT);
	oled.sendBuffer();
}

void new_menu_function() {
	interaction_handler();
	display_menu();
}
