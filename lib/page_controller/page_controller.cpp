#include "page_controller.h"
#include <Arduino.h>
#include <keyboard.h>

DisplayFunction current_function = ((void (*)(void))0);

static long last_interacted = 0;
static long interact_interval_ms = 1500;

bool page_selectable = true;

void page_controller_init(void)
{

	set_display_function(home_page_function, home_page_initialize);

	last_interacted = millis();

	register_page_display(PageDisplay("Home Page", home_page_function, home_page_initialize));
	register_page_display(PageDisplay("Kbd Test Page", keyboard_test_page_function, keyboard_test_page_initialize));
}

void set_display_function(DisplayFunction function, InitializeFunction initialize_function)
{
	current_function = function;
	if (initialize_function)
	{
		initialize_function();
	}
}

void display_one_frame(void)
{
	if (current_function)
	{
		current_function();
	}
}

// 请在 loop() 中调用该函数
void page_controller_loop(void)
{
	display_one_frame();

	if (IS_KEY_RELEASING(KEY_A) || IS_KEY_RELEASING(KEY_B))
	{
		last_interacted = millis();
	}

	long current_time_ms = millis();
	if (current_time_ms - last_interacted >= interact_interval_ms)
	{
		if (page_selectable && current_function != page_select_function)
		{
			set_display_function(page_select_function, page_select_initialize);
		}
	}
}