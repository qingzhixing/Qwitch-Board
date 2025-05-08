#include "page_controller.h"
#include <oled.h>
#include <Arduino.h>
#include <keyboard.h>

#define MAX_PAGE_AMOUNT 2
static int current_page = 0;
static bool hide_info = false;

static long last_interacted_tick_ms = 0;
// 连续交互间隔
static long interact_interval_ms = 200;

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
		current_page = (current_page - 1 + MAX_PAGE_AMOUNT) % MAX_PAGE_AMOUNT;
	}
	if (IS_KEY_PRESSING(KEY_RIGHT) && can_interact())
	{
		update_last_interacted_tick();
		need_update_select_screen = true;
		current_page = (current_page + 1) % MAX_PAGE_AMOUNT;
	}

	if (IS_KEY_PRESSING(KEY_A) && can_interact() && hide_info)
	{
		update_last_interacted_tick();
		switch (current_page)
		{
		case 0: // Home page
			set_display_function(home_page_function, home_page_initialize);
			break;
		case 1: // Keyboard test page
			set_display_function(keyboard_test_page_function, keyboard_test_page_initialize);
			break;
		default:
			break;
		}
	}

	if (need_update_select_screen && hide_info)
	{
		auto display_str = "";
		switch (current_page)
		{
		case 0: // Home page
			display_str = "@[Home page]";
			break;
		case 1: // Keyboard test page
			display_str = "@[kbd test page]";
			break;
		default:
			display_str = "!!Unknown page [X]!!";
			break;
		}

		oled.setDrawColor(0);
		oled.drawBox(0, 21, 128, 16);
		oled.setDrawColor(1);
		oled.drawStr(20, 31, display_str);
		oled.drawStr(15, 47, "Press A to enter");
		oled.sendBuffer();
	}
}
