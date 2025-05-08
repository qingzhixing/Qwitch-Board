#include "keyboard.hpp"

void keyboard_init()
{
	pinMode(KEY_UP, INPUT_PULLUP);
	pinMode(KEY_DOWN, INPUT_PULLUP);
	pinMode(KEY_LEFT, INPUT_PULLUP);
	pinMode(KEY_RIGHT, INPUT_PULLUP);
	pinMode(KEY_A, INPUT_PULLUP);
	pinMode(KEY_B, INPUT_PULLUP);
}