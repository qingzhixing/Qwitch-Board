#include "page_controller.hpp"
#include <oled.hpp>
#include <Arduino.h>
#include <keyboard.hpp>
#include <vector>
#include <interacter.hpp>

static std::vector<PageDisplay> page_displays;

#define PAGE_AMOUNT (page_displays.size())

// 连续交互间隔
static Interacter interacter(200);
static int current_page = 0;
static bool hide_info = true;
static bool need_update_select_screen = false;

void register_page_display(PageDisplay &&page_display)
{
	page_displays.emplace_back(std::move(page_display));
}
void display_page_select_info(void)
{
	oled.clearBuffer();

	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(30, 12, "Select Info");
	oled.setDrawColor(1);

	oled.drawStr(5, 31, "Press A to select ");
	oled.drawStr(5, 47, "Press L/R to switch");
	oled.drawStr(5, 63, "Press B to on/off info");

	oled.sendBuffer();
	hide_info = false;
}

void page_select_initialize(void)
{
	interacter.update_interaction_tick();

	// 冷却500ms
	interacter.add_cooldown(500);

	need_update_select_screen = true;
}

void page_select_function(void)
{
	if (page_displays.empty())
	{
		oled.clearBuffer();
		oled.drawStr(30, 10, "!!ERROR!!");
		oled.drawStr(5, 31, "No registered page!");
		oled.sendBuffer();
		return;
	}

	if (IS_KEY_PRESSING(KEY_B) && interacter.can_interact())
	{
		interacter.update_interaction_tick();
		hide_info = !hide_info;
		if (!hide_info)
		{
			display_page_select_info();
		}
		else
		{
			oled.clearBuffer();
			oled.sendBuffer();

			need_update_select_screen = true;
		}
	}

	if (IS_KEY_PRESSING(KEY_LEFT) && interacter.can_interact() && hide_info)
	{
		interacter.update_interaction_tick();
		need_update_select_screen = true;
		current_page = (current_page - 1 + PAGE_AMOUNT) % PAGE_AMOUNT;
	}
	if (IS_KEY_PRESSING(KEY_RIGHT) && interacter.can_interact())
	{
		interacter.update_interaction_tick();
		need_update_select_screen = true;
		current_page = (current_page + 1) % PAGE_AMOUNT;
	}

	if (IS_KEY_PRESSING(KEY_A) && interacter.can_interact() && hide_info)
	{
		interacter.update_interaction_tick();
		auto &page_display = page_displays[current_page];
		set_display_function(page_display.function, page_display.initialize_function);
	}

	if (need_update_select_screen && hide_info)
	{
		char display_str[32] = {};
		auto &page_display = page_displays[current_page];
		snprintf(display_str, sizeof(display_str), "@[%s]", page_display.page_name);

		oled.clearBuffer();
		oled.drawBox(0, 21, 128, 16);
		oled.setDrawColor(0);
		oled.drawStr(10, 33, display_str);
		oled.setDrawColor(1);

		oled.drawStr(15, 47, "Press A to enter");
		oled.drawStr(15, 63, "Press B to info");
		oled.sendBuffer();
	}
}
