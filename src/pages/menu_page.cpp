#include "pages/menu_page.hpp"
#include <bitmaps.hpp>
#include <curves.hpp>
#include <interaction.hpp>
#include <keyboard.hpp>
#include <oled.hpp>
#include "page_controller.hpp"

enum MenuAnimationState
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_STOP
};

// Animation
static MenuAnimationState animation_state;
static long animation_duration_ms = 800;
static long animation_start_tick_ms = 0;
static long animation_delta_y = 0;

NewPageDisplay* menu_page = new MenuPage();

// 连续交互间隔
static Interaction interaction(500);

static int current_page_index = 0;


void menu_initialize()
{
    interaction.update_interaction_tick();
    interaction.add_cooldown(300);
    oled.clearBuffer();
}

static void interaction_handler()
{
    if (is_key_on_pressed(KEY_A))
    {
        set_new_display_function(new_page_displays[current_page_index]);
        interaction.update_interaction_tick();
        return;
    }

    const auto page_amount = static_cast<int>(new_page_displays.size());
    if (is_key_on_pressed(KEY_UP) || (is_key_pressing(KEY_UP) && interaction.can_interact()))
    {
        current_page_index = (current_page_index - 1 + page_amount) % page_amount;
        animation_state = MOVE_UP;
        animation_start_tick_ms = static_cast<long>(millis());
        interaction.update_interaction_tick();
        return;
    }

    if (is_key_on_pressed(KEY_DOWN) || (is_key_pressing(KEY_DOWN) && interaction.can_interact()))
    {
        current_page_index = (current_page_index + 1) % page_amount;
        animation_state = MOVE_DOWN;
        animation_start_tick_ms = static_cast<long>(millis());
        interaction.update_interaction_tick();
        return;
    }
}

static void display_menu()
{
    const auto page_amount = static_cast<int>(new_page_displays.size());

    const NewPageDisplay* new_current_page = nullptr;

    oled.clearBuffer();

    // previous element

    new_current_page = new_page_displays[(current_page_index - 2 + page_amount) % page_amount];
    oled.drawXBM(4, -20 + animation_delta_y, 16, 16, new_current_page->get_icon());
    oled.setFont(MENU_NORMAL_FONT);
    oled.drawStr(24, -7 + animation_delta_y, new_current_page->get_name().c_str());


    // first element
    new_current_page = new_page_displays[(current_page_index - 1 + page_amount) % page_amount];
    oled.drawXBM(4, 2 + animation_delta_y, 16, 16, new_current_page->get_icon());
    // oled.drawXBM(0, 0 + animation_delta_y, 128, 20, background_normal_bits);
    oled.setFont(MENU_NORMAL_FONT);
    oled.drawStr(24, 15 + animation_delta_y, new_current_page->get_name().c_str());

    // second element
    new_current_page = new_page_displays[current_page_index];
    oled.drawXBM(4, 24 + animation_delta_y, 16, 16, new_current_page->get_icon());
    // oled.drawXBM(0, 22 + animation_delta_y, 128, 20, background_center_bits);
    oled.drawXBM(0, 22 + animation_delta_y, 128, 20, background_normal_bits);
    oled.setFont(MENU_BOLD_FONT);
    oled.drawStr(24, 37 + animation_delta_y, new_current_page->get_name().c_str());

    // third element
    new_current_page = new_page_displays[(current_page_index + 1) % page_amount];
    oled.drawXBM(4, 46 + animation_delta_y, 16, 16, new_current_page->get_icon());
    // oled.drawXBM(0, 44 + animation_delta_y, 128, 20, background_normal_bits);
    oled.setFont(MENU_NORMAL_FONT);
    oled.drawStr(24, 58 + animation_delta_y, new_current_page->get_name().c_str());

    // next element
    new_current_page = new_page_displays[(current_page_index + 2) % page_amount];
    oled.drawXBM(4, 68 + animation_delta_y, 16, 16, new_current_page->get_icon());
    oled.setFont(MENU_NORMAL_FONT);
    oled.drawStr(24, 80 + animation_delta_y, new_current_page->get_name().c_str());


    oled.setFont(TEXT_NORMAL_FONT);
    oled.sendBuffer();
}

static void animation_handler()
{
    if (animation_state == MOVE_STOP)
    {
        return;
    }
    // animation started time
    const auto current = static_cast<long>(millis());
    const auto elapsed = current - animation_start_tick_ms;
    if (elapsed > animation_duration_ms)
    {
        animation_state = MOVE_STOP;
    }
    const auto animation_process = 1.0f * static_cast<float>(elapsed) / static_cast<float>(animation_duration_ms);

    if (animation_state == MOVE_UP)
    {
        animation_delta_y = static_cast<long>(lerp(-22, 0, easeOutQuint(animation_process)));
    }
    else if (animation_state == MOVE_DOWN)
    {
        animation_delta_y = static_cast<long>(lerp(22, 0, easeOutQuint(animation_process)));
    }
}

void menu_update()
{
    interaction_handler();
    animation_handler();
    display_menu();
}

void MenuPage::update() const { menu_update(); }
void MenuPage::initialize() const { menu_initialize(); }
std::string MenuPage::get_name() const { return MENU_PAGE_NAME; }
const unsigned char* MenuPage::get_icon() const { return icon_smile_bits; }
