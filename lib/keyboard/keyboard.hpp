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

#define IS_KEY_PRESSING(key) (digitalRead(key) == KEY_PRESSING)
#define IS_KEY_RELEASING(key) (digitalRead(key) == KEY_RELEASING)

void keyboard_init();

#endif // !_KEYBOARD_H_