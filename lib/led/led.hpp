#pragma once
#ifndef LED_H_
#define LED_H_

#include <Arduino.h>

#define LED_PIN (GPIO_NUM_2)
void led_init();
void led_on();
void led_off();
bool is_led_on();
void toggle_led();

#endif // LED_H_