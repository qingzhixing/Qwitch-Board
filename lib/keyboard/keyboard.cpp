#include "keyboard.hpp"
#include <map>

static KeyboardState default_state = {
	.is_pressing = false,
	.on_pressed = false,
	.on_released = false,
	.previous_pressing = false,
};
static std::map<gpio_num_t, KeyboardState> key_state;

void keyboard_init()
{
	pinMode(KEY_UP, INPUT_PULLUP);
	pinMode(KEY_DOWN, INPUT_PULLUP);
	pinMode(KEY_LEFT, INPUT_PULLUP);
	pinMode(KEY_RIGHT, INPUT_PULLUP);
	pinMode(KEY_A, INPUT_PULLUP);
	pinMode(KEY_B, INPUT_PULLUP);

	key_state[KEY_UP] = default_state;
	key_state[KEY_DOWN] = default_state;
	key_state[KEY_LEFT] = default_state;
	key_state[KEY_RIGHT] = default_state;
	key_state[KEY_A] = default_state;
	key_state[KEY_B] = default_state;
}

static void update_single_key(gpio_num_t key)
{
	bool current_pressing = digitalRead(key) == KEY_PRESSING;
	bool previous_pressing = key_state[key].previous_pressing;
	bool on_pressed = !previous_pressing && current_pressing;
	bool on_released = previous_pressing && !current_pressing;

	key_state[key] = {
		.is_pressing = current_pressing,
		.on_pressed = on_pressed,
		.on_released = on_released,
		.previous_pressing = current_pressing,
	};
}

// 请在每个loop()中调用update_keyboard_state()来更新键盘状态
void update_keyboard_state()
{
	update_single_key(KEY_UP);
	update_single_key(KEY_DOWN);
	update_single_key(KEY_LEFT);
	update_single_key(KEY_RIGHT);
	update_single_key(KEY_A);
	update_single_key(KEY_B);
}

KeyboardState get_keyboard_state(gpio_num_t key)
{
	// 没有这个按键
	if (key_state.find(key) == key_state.end())
	{
		return default_state;
	}
	return key_state[key];
}

bool is_key_pressing(gpio_num_t key)
{
	return get_keyboard_state(key).is_pressing;
}
bool is_key_releasing(gpio_num_t key)
{
	return !get_keyboard_state(key).is_pressing;
}
bool is_key_on_pressed(gpio_num_t key)
{
	return get_keyboard_state(key).on_pressed;
}
bool is_key_on_released(gpio_num_t key)
{
	return get_keyboard_state(key).on_released;
}