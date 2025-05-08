#include "led.hpp"

void led_init()
{
	pinMode(2, OUTPUT);
	led_off();
}
void led_on()
{
	digitalWrite(2, HIGH);
}
void led_off()
{
	digitalWrite(2, LOW);
}