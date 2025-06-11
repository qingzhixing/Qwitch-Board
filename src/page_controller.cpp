#include "page_controller.hpp"
#include <games/game_2048/Game2048Page.hpp>
#include <interaction.hpp>
#include <keyboard.hpp>
#include <pages/nvs_data_page.hpp>

#include "pages/animation_page.hpp"
#include "pages/bluetooth_info_page.hpp"
#include "pages/home_page.hpp"
#include "pages/keyboard_test_page.hpp"
#include "pages/led_test_page.hpp"
#include "pages/menu_page.hpp"
#include "pages/speaker_test_page.hpp"

std::vector<const NewPageDisplay*> new_page_displays;
static const NewPageDisplay* new_current_page(nullptr);

static Interaction interaction(1500);
static bool initialized = false;

bool page_selectable = true;

void register_new_page_display(const NewPageDisplay* page_display) { new_page_displays.push_back(page_display); }

void page_controller_init()
{
    set_new_display_function(home_page);

    register_new_page_display(home_page);
    register_new_page_display(keyboard_test_page);
    register_new_page_display(speaker_test_page);
    register_new_page_display(led_test_page);
    register_new_page_display(animation_page);
    register_new_page_display(nvs_data_page);
    register_new_page_display(game_2048_page);
    register_new_page_display(bluetooth_info_page);

}
void set_new_display_function(const NewPageDisplay* new_page_display) { new_current_page = new_page_display; }

void display_one_frame()
{
    if (new_current_page == nullptr)
        return;

    if (!initialized)
    {
        new_current_page->initialize();
        initialized = true;
    }

    new_current_page->update();
}

// 请在 loop() 中调用该函数
void page_controller_loop()
{
    display_one_frame();

    if (!is_page_select_key_pressing())
    {
        interaction.update_interaction_tick();
    }

    if (interaction.can_interact())
    {
        interaction.update_interaction_tick();
        if (page_selectable && new_current_page->get_name() != MENU_PAGE_NAME)
        {
            set_new_display_function(menu_page);
        }
    }
}
