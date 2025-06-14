#include "pages/speaker_test_page.hpp"
#include <interaction.hpp>
#include <keyboard.hpp>
#include <oled.hpp>
#include <speaker.hpp>

#include "bitmaps.hpp"

static Interaction interaction(100);

NewPageDisplay* speaker_test_page = new SpeakerTestPage();

void speaker_test_page_initialize() { interaction.add_cooldown(300); }

static void display_speaker_info()
{
    char buffer[32]{};

    oled.clearBuffer();
    oled.drawBox(0, 0, 128, 16);
    oled.setDrawColor(0);
    oled.drawStr(30, 12, "Speaker Test");
    oled.setDrawColor(1);

    snprintf(buffer, sizeof(buffer), "[L/R] Freq: %d Hz", get_speaker_frequency_hz());
    oled.drawStr(0, 25, buffer);

    snprintf(buffer, sizeof(buffer), "[U/D] Volume: %.2f", get_speaker_volumn_percent());
    oled.drawStr(0, 37, buffer);

    sniprintf(buffer, sizeof(buffer), "[A] On/Off: %s", is_speaker_on() ? "On" : "Off");
    oled.drawStr(0, 49, buffer);

    oled.sendBuffer();
}

static void handle_speaker_interaction()
{
    if (is_page_select_key_pressing())
    {
        return;
    }

    if (is_key_pressing(KEY_LEFT) && interaction.can_interact())
    {
        set_speaker_frequency(get_speaker_frequency_hz() - 100);
        interaction.update_interaction_tick();
        return;
    }
    if (is_key_pressing(KEY_RIGHT) && interaction.can_interact())
    {
        set_speaker_frequency(get_speaker_frequency_hz() + 100);
        interaction.update_interaction_tick();
        return;
    }
    if (is_key_pressing(KEY_UP) && interaction.can_interact())
    {
        set_speaker_volume_percent(get_speaker_volumn_percent() + 0.05f);
        interaction.update_interaction_tick();
        return;
    }
    if (is_key_pressing(KEY_DOWN) && interaction.can_interact())
    {
        set_speaker_volume_percent(get_speaker_volumn_percent() - 0.05f);
        interaction.update_interaction_tick();
        return;
    }
    if (is_key_on_pressed(KEY_A))
    {
        toggle_speaker();
        return;
    }
}

void speaker_test_page_update()
{
    handle_speaker_interaction();
    display_speaker_info();
}

void SpeakerTestPage::update() const { speaker_test_page_update(); }
void SpeakerTestPage::initialize() const { speaker_test_page_initialize(); }
std::string SpeakerTestPage::get_name() const { return "Speaker Test"; }
const unsigned char* SpeakerTestPage::get_icon() const { return icon_speaker_bits; }
