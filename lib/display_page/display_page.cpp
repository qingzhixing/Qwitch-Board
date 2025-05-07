#include "display_page.h"

static DisplayFunction current_function = ((void (*)(void))0);

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