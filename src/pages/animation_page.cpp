#include "pages/animation_page.hpp"
#include <Arduino.h>
#include <curves.hpp>
#include <oled.hpp>

#include "bitmaps.hpp"

NewPageDisplay* animation_page = new AnimationPage();

static bool move_right = true;
static int start_x = 20;
static int destination_x = 87;
static long animation_start_tick_ms = 0;
static int animation_duration_ms = 800;

void animation_page_initialize() { animation_start_tick_ms = static_cast<long>(millis()); }

void animation_page_update()
{
    long current_tick_ms = static_cast<long>(millis());
    int elapsed_time_ms = current_tick_ms - animation_start_tick_ms;
    // calculate the animation process
    float animation_progress = static_cast<float>(elapsed_time_ms) / static_cast<float>(animation_duration_ms);

    // calculate the animation value
    const int now_x = static_cast<int>(
        lerp(static_cast<float>(start_x), static_cast<float>(destination_x), easeInOutBack(animation_progress)));

    // update the display
    oled.clearBuffer();
    oled.drawBox(now_x, 30, 10, 4);
    oled.sendBuffer();

    // update the animation process
    if (animation_progress >= 1.0)
    {
        animation_start_tick_ms = current_tick_ms;
        move_right = !move_right;
        if (move_right)
        {
            start_x = 20;
            destination_x = 87;
        }
        else
        {
            start_x = 87;
            destination_x = 20;
        }
    }
}

void AnimationPage::update() const { animation_page_update(); }

void AnimationPage::initialize() const { animation_page_initialize(); }

std::string AnimationPage::get_name() const { return "Animation Page"; }

const unsigned char* AnimationPage::get_icon() const { return icon_ball_bits; }
