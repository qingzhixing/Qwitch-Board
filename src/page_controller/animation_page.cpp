#include "page_controller/animation_page.hpp"
#include <Arduino.h>
#include <curves.hpp>
#include <oled.hpp>

static bool move_right = true;
static int start_x = 10;
static int destinate_x = 100;
static long animation_start_tick_ms = 0;
static int animation_duration_ms = 500;

void animation_page_initialize()
{
	animation_start_tick_ms = millis();
}

void animation_page_function()
{
	long current_tick_ms = millis();
	int elapsed_time_ms = current_tick_ms - animation_start_tick_ms;
	// calculate the animation process
	float animation_progress = (float)elapsed_time_ms / animation_duration_ms;

	// calculate the animation value
	int now_x = lerp(start_x, destinate_x, easeOutQuint(animation_progress));

	// update the display
	oled.clearBuffer();
	oled.drawBox(now_x, 30, 10, 4);
	oled.sendBuffer();

	// update the animation process
	if (animation_progress >= 1.0)
	{
		animation_start_tick_ms = current_tick_ms;
		move_right = !move_right;
		if (move_right)
		{
			start_x = 10;
			destinate_x = 100;
		}
		else
		{
			start_x = 100;
			destinate_x = 10;
		}
	}
}