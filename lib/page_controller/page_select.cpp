#include "page_controller.h"
#include <oled.h>
#include <Arduino.h>
#include <keyboard.h>
#include <vector>

static std::vector<PageDisplay> page_displays;

#define PAGE_AMOUNT (page_displays.size())

static int current_page = 0;
static bool hide_info = false;

static long last_interacted_tick_ms = 0;
// 连续交互间隔
static long interact_interval_ms = 200;

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

	oled.clearDisplay();
	oled.clearBuffer();

	oled.drawStr(30, 10, "Page Select :)");
	oled.drawStr(5, 31, "Press A to select ");
	oled.drawStr(5, 47, "Press L/R to switch");
	oled.drawStr(5, 63, "Press B to on/off info");

	oled.sendBuffer();
	hide_info = false;
}

void page_select_initialize(void)
{
	display_page_select_info();
	update_last_interacted_tick();

	// 冷却500ms
	last_interacted_tick_ms += 500;
}

void page_select_function(void)
{
	if (page_displays.empty())
	{
		oled.clearDisplay();
		oled.clearBuffer();
		oled.drawStr(30, 10, "!!ERROR!!");
		oled.drawStr(5, 31, "No registered page!");
		oled.sendBuffer();
		return;
	}

	bool need_update_select_screen = false;

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
			oled.clearDisplay();
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

		oled.setDrawColor(0);
		oled.drawBox(0, 21, 128, 16);
		oled.setDrawColor(1);
		oled.drawStr(20, 31, display_str);
		oled.drawStr(15, 47, "Press A to enter");
		oled.sendBuffer();
	}
}
