#include "led.hpp"

// 1: on, 0: off
static bool led_state = false;

void led_init()
{
	pinMode(2, OUTPUT);
	led_off();
}
void led_on()
{
	led_state = true;
	digitalWrite(2, HIGH);
}
void led_off()
{
	led_state = false;
	digitalWrite(2, LOW);
}

bool is_led_on()
{
	return led_state;
}

void toggle_led()
{
	if (led_state)
	{
		led_off();
	}
	else
	{
		led_on();
	}
}
