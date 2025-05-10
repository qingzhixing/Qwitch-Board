#pragma once

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <Arduino.h>

#define KEY_UP (GPIO_NUM_27)
#define KEY_DOWN (GPIO_NUM_14)
#define KEY_LEFT (GPIO_NUM_12)
#define KEY_RIGHT (GPIO_NUM_13)
#define KEY_A (GPIO_NUM_33)
#define KEY_B (GPIO_NUM_32)

#define KEY_PRESSING HIGH
#define KEY_RELEASING LOW

typedef struct KeyboardState
{
	bool is_pressing;
	bool on_pressed;
	bool on_released;
	bool previous_pressing;
} KeyboardState;

void keyboard_init();

// 请在每个loop()中调用update_keyboard_state()来更新键盘状态
void update_keyboard_state();

KeyboardState get_keyboard_state(gpio_num_t key);

bool is_key_pressing(gpio_num_t key);
bool is_key_releasing(gpio_num_t key);
bool is_key_on_pressed(gpio_num_t key);
bool is_key_on_released(gpio_num_t key);

inline bool is_page_select_key_pressing()
{
	return is_key_pressing(KEY_A) && is_key_pressing(KEY_B);
}

#endif // !_KEYBOARD_H_