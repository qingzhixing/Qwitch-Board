#include "page_controller.h"
#include <Arduino.h>
#include <keyboard.h>

static DisplayFunction current_function = ((void (*)(void))0);

static long last_released_AB_time_ms = 0;
static long switch_page_interval_ms = 3000;

static bool is_in_home_page = true;

void page_controller_init(void)
{

	set_display_function(home_page_function, home_page_initialize);

	last_released_AB_time_ms = millis();
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
	if ((digitalRead(KEY_A) == KEY_PRESSED) && (digitalRead(KEY_B) == KEY_PRESSED))
	{
		long current_time_ms = millis();
		if (current_time_ms - last_released_AB_time_ms >= switch_page_interval_ms)
		{
			last_released_AB_time_ms = millis();
			if (is_in_home_page)
			{
				is_in_home_page = false;
				set_display_function(keyboard_test_page_function, keyboard_test_page_initialize);
			}
			else
			{
				is_in_home_page = true;
				set_display_function(home_page_function, home_page_initialize);
			}
		}
	}
	else
	{
		last_released_AB_time_ms = millis();
	}
	display_one_frame();
}