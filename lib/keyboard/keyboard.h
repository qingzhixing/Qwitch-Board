#pragma once

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <Arduino.h>

#define KEY_UP (27U)
#define KEY_DOWN (14U)
#define KEY_LEFT (12U)
#define KEY_RIGHT (13U)
#define KEY_A (33U)
#define KEY_B (32U)

#define KEY_PRESSED HIGH
#define KEY_RELEASED LOW

void keyboard_init();

#endif // !_KEYBOARD_H_