#pragma once
#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>

#define LED_PIN (GPIO_NUM_2)
void led_init();
void led_on();
void led_off();

#endif // !_LED_H_