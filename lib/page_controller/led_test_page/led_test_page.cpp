#include "led_test_page.hpp"

#include <interacter.hpp>
#include <page_controller.hpp>
#include <oled.hpp>

static Interacter interacter(200);

void led_test_page_init()
{
	interacter.update_interaction_tick();
	interacter.add_cooldown(500);
}

static void interaction_handler()
{
	if (!interacter.can_interact())
		return;
	if (is_page_select_key_pressing())
		return;

	if (IS_KEY_PRESSING(KEY_A))
	{
		toggle_led();
		interacter.update_interaction_tick();
	}
}
static void display_handler()
{
	oled.clearBuffer();
	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(30, 12, "LED Test");
	oled.setDrawColor(1);

	if (is_led_on())
	{
		oled.drawBox(5, 21, 128 - 6 * 2 - 1, 64 - 6 * 2 - 1 - 16);
		oled.setDrawColor(0);
		oled.drawStr(25, 41, "[A] LED ON");
		oled.setDrawColor(1);
	}
	else
	{
		oled.drawFrame(5, 21, 128 - 6 * 2 - 1, 64 - 6 * 2 - 1 - 16);
		oled.drawStr(25, 41, "[A] LED OFF");
	}
	oled.sendBuffer();
}

void led_test_page_function()
{
	interaction_handler();
	display_handler();
}