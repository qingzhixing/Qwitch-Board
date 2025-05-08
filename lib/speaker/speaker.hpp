#pragma once

#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include <Arduino.h>
#include <driver/ledc.h>

#define LEDC_CHANNEL LEDC_CHANNEL_0
// 8位分辨率
#define LEDC_DUTY_RESOLUTION LEDC_TIMER_8_BIT
#define MAX_DUTY (1 << LEDC_DUTY_RESOLUTION - 1)
// 使用定时器0
#define LEDC_TIMER LEDC_TIMER_0
// 速度模式
#define LEDC_SPEED_MODE LEDC_HIGH_SPEED_MODE
// 自动选择时钟源
#define LEDC_CLOCK_CONFIG LEDC_AUTO_CLK
// 相位（通常为0）
#define LEDC_CHANNEL_HPOINT 0

#define SPEAKER_PIN GPIO_NUM_23

// PWM频率
uint16_t get_speaker_frequncy_hz();
float get_speaker_volumn_percent();

void speaker_init();

void speaker_on();
void speaker_off();
bool is_speaker_on();
void toggle_speaker();

void set_speaker_volume_percent(float volume);
void set_speaker_frequency(int32_t frequency);

#endif // !_SPEAKER_H_