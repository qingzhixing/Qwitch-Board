#include <Arduino.h>
#include <U8g2lib.h>
#include <keyboard.hpp>
#include <oled.hpp>
#include <page_controller/page_controller.hpp>
#include <led.hpp>
#include <speaker.hpp>

void setup()
{
	oled_init();
	keyboard_init();
	led_init();
	speaker_init();
	Serial.begin(115200);

	led_on();

	page_controller_init();
}

void loop()
{
	// 硬件事件
	update_keyboard_state();

	// 交互逻辑
	page_controller_loop();
}