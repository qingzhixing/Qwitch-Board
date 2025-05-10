#include "page_controller/page_controller.hpp"
#include <interacter.hpp>
#include "page_controller//keyboard_test_page.hpp"
#include "page_controller//home_page.hpp"
#include "page_controller//speaker_test_page.hpp"
#include "page_controller//led_test_page.hpp"

DisplayFunction current_function = ((void (*)(void))0);

static Interacter interacter(1500);

bool page_selectable = true;

void page_controller_init(void)
{

	set_display_function(home_page_function, home_page_initialize);

	register_page_display(PageDisplay("Home Page", home_page_function, home_page_initialize));
	register_page_display(PageDisplay("Kbd Test Page", keyboard_test_page_function, keyboard_test_page_initialize));
	register_page_display(PageDisplay("Speaker Test Page", speaker_test_page_function, speaker_test_page_initialize));
	register_page_display(PageDisplay("LED Test Page", led_test_page_function, led_test_page_init));
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

	if (!is_page_select_key_pressing())
	{
		interacter.update_interaction_tick();
	}

	long current_time_ms = millis();
	if (interacter.can_interact())
	{
		interacter.update_interaction_tick();
		if (page_selectable && current_function != page_select_function)
		{
			set_display_function(page_select_function, page_select_initialize);
		}
	}
}