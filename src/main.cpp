#include <Arduino.h>
#include <hardware.hpp>
#include <keyboard.hpp>
#include <oled.hpp>
#include <page_controller.hpp>
#include <led.hpp>
#include <speaker.hpp>
#include <nvs_controller.hpp>

void setup() {
	oled_init();
	keyboard_init();
	led_init();
	speaker_init();
	Serial.begin(115200);

	led_on();

	page_controller_init();
	nvs_controller_init();
}

void loop() {
	// 硬件事件
	update_keyboard_state();

	hardware_record();

	// 交互逻辑
	page_controller_loop();
}
