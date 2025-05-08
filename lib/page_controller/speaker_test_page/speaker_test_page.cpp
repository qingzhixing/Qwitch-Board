#include "speaker_test_page.hpp"
#include <speaker.hpp>
#include <oled.hpp>
#include <page_controller.hpp>
#include <interacter.hpp>

static Interacter interacter(100);

void speaker_test_page_initialize()
{
	interacter.add_cooldown(1000);
}

static void display_speaker_info()
{
	char buffer[32]{};

	oled.clearBuffer();
	oled.drawBox(0, 0, 128, 16);
	oled.setDrawColor(0);
	oled.drawStr(30, 12, "Speaker Test");
	oled.setDrawColor(1);

	snprintf(buffer, sizeof(buffer), "[L/R] Freq: %d Hz", get_speaker_frequncy_hz());
	oled.drawStr(0, 25, buffer);

	snprintf(buffer, sizeof(buffer), "[U/D] Volume: %.2f", get_speaker_volumn_percent());
	oled.drawStr(0, 37, buffer);

	sniprintf(buffer, sizeof(buffer), "[A] On/Off: %s", is_speaker_on() ? "On" : "Off");
	oled.drawStr(0, 49, buffer);

	oled.sendBuffer();
}

static void handle_speaker_interaction()
{
	if (!interacter.can_interact())
		return;

	if (is_page_select_key_pressing())
	{
		return;
	}

	if (IS_KEY_PRESSING(KEY_LEFT))
	{
		set_speaker_frequency(get_speaker_frequncy_hz() - 100);
		interacter.update_interaction_tick();
		return;
	}
	if (IS_KEY_PRESSING(KEY_RIGHT))
	{
		set_speaker_frequency(get_speaker_frequncy_hz() + 100);
		interacter.update_interaction_tick();
		return;
	}
	if (IS_KEY_PRESSING(KEY_UP))
	{
		set_speaker_volume_percent(get_speaker_volumn_percent() + 0.05);
		interacter.update_interaction_tick();
		return;
	}
	if (IS_KEY_PRESSING(KEY_DOWN))
	{
		set_speaker_volume_percent(get_speaker_volumn_percent() - 0.05);
		interacter.update_interaction_tick();
		return;
	}
	if (IS_KEY_PRESSING(KEY_A))
	{
		toggle_speaker();
		interacter.update_interaction_tick();
		return;
	}
}

void speaker_test_page_function()
{
	handle_speaker_interaction();
	display_speaker_info();
}