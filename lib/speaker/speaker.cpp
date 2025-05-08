#include "speaker.hpp"

static float speaker_volumn_percent = 0.1;
static bool _is_speaker_on = false;

static ledc_timer_config_t timer_config = {
	.speed_mode = LEDC_SPEED_MODE,
	.duty_resolution = LEDC_DUTY_RESOLUTION,
	.timer_num = LEDC_TIMER,
	.freq_hz = 2000,
	.clk_cfg = LEDC_CLOCK_CONFIG,
};

static ledc_channel_config_t channel_config = {
	.gpio_num = SPEAKER_PIN,
	.speed_mode = LEDC_SPEED_MODE,
	.channel = LEDC_CHANNEL,
	.timer_sel = LEDC_TIMER,
	.duty = 0, // 初始占空比为0
	.hpoint = LEDC_CHANNEL_HPOINT,
};

uint16_t get_speaker_frequncy_hz()
{
	return timer_config.freq_hz;
}

float get_speaker_volumn_percent()
{
	return speaker_volumn_percent;
}

static uint16_t volumn_to_duty(float volume)
{
	if (volume < 0)
	{
		return 0;
	}
	if (volume > 1)
	{
		return MAX_DUTY;
	}
	return (uint16_t)(volume * MAX_DUTY);
}

static void setup_pwm()
{
	// 配置LEDC定时器
	ledc_timer_config(&timer_config);

	// 配置LEDC通道
	ledc_channel_config(&channel_config);
}

void set_speaker_volume_percent(float volume)
{
	if (volume < 0)
		volume = 0;
	if (volume > 1)
		volume = 1;
	speaker_volumn_percent = volume;
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL, volumn_to_duty(speaker_volumn_percent));
	if (_is_speaker_on)
	{
		ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL);
	}
}

void set_speaker_frequency(int32_t frequency)
{
	if (frequency < 0)
		frequency = 0;
	if (frequency > 20000)
		frequency = 20000;
	timer_config.freq_hz = frequency;
	ledc_timer_config(&timer_config);
}

void speaker_on()
{
	_is_speaker_on = true;
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL, volumn_to_duty(speaker_volumn_percent));
	ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL);
}
void speaker_off()
{
	_is_speaker_on = false;
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL, 0);
	ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL);
}

bool is_speaker_on()
{
	return _is_speaker_on;
}

void toggle_speaker()
{
	if (_is_speaker_on)
	{
		speaker_off();
	}
	else
	{
		speaker_on();
	}
}

void speaker_init()
{
	pinMode(SPEAKER_PIN, OUTPUT);
	setup_pwm();
	speaker_off();
}