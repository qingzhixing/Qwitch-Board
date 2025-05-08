#include "page_controller.h"
#include <oled.h>
#include <Arduino.h>
#include <keyboard.h>
#include <vector>

static std::vector<PageDisplay> page_displays;

#define PAGE_AMOUNT (page_displays.size())

// 连续交互间隔
static long interact_interval_ms = 200;
static long last_interacted_tick_ms = 0;
static int current_page = 0;
static bool hide_info = true;
static bool need_update_select_screen = false;

void register_page_display(PageDisplay &&page_display)
{
	page_displays.emplace_back(std::move(page_display));
}

inline bool can_interact()
{
	return (long(millis()) - last_interacted_tick_ms) > interact_interval_ms;
}

inline void update_last_interacted_tick()
{
	last_interacted_tick_ms = millis();
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
	update_last_interacted_tick();

	// 冷却500ms
	last_interacted_tick_ms += 500;

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

	if (IS_KEY_PRESSING(KEY_B) && can_interact())
	{
		update_last_interacted_tick();
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

	if (IS_KEY_PRESSING(KEY_LEFT) && can_interact() && hide_info)
	{
		update_last_interacted_tick();
		need_update_select_screen = true;
		current_page = (current_page - 1 + PAGE_AMOUNT) % PAGE_AMOUNT;
	}
	if (IS_KEY_PRESSING(KEY_RIGHT) && can_interact())
	{
		update_last_interacted_tick();
		need_update_select_screen = true;
		current_page = (current_page + 1) % PAGE_AMOUNT;
	}

	if (IS_KEY_PRESSING(KEY_A) && can_interact() && hide_info)
	{
		update_last_interacted_tick();
		auto &page_display = page_displays[current_page];
		set_display_function(page_display.function, page_display.initialize_function);
	}

	if (need_update_select_screen && hide_info)
	{
		char display_str[32] = {};
		auto &page_display = page_displays[current_page];
		snprintf(display_str, sizeof(display_str), "@[%s]", page_display.page_name);

		oled.clearBuffer();
		oled.drawBox(10, 21, 108, 16);
		oled.setDrawColor(0);
		oled.drawStr(20, 33, display_str);
		oled.setDrawColor(1);

		oled.drawStr(15, 47, "Press A to enter");
		oled.drawStr(15, 63, "Press B to info");
		oled.sendBuffer();
	}
}
