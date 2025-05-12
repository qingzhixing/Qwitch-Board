#include "page_controller.hpp"
#include <interaction.hpp>
#include <keyboard.hpp>

#include "pages/keyboard_test_page.hpp"
#include "pages/home_page.hpp"
#include "pages/speaker_test_page.hpp"
#include "pages/led_test_page.hpp"
#include "pages/animation_page.hpp"
#include "pages/new_menu.hpp"
#include "pages/menu_page.hpp"

std::vector<PageDisplay> page_displays{};

static PageDisplay current_page(nullptr, nullptr);

static Interaction interaction(1500);
static bool initialized = false;

bool page_selectable = true;

void register_page_display(PageDisplay &&page_display) {
	page_displays.emplace_back(page_display);
}

void register_page_display(const PageDisplay &page_display) {
	page_displays.push_back(page_display);
}

void page_controller_init() {
	set_display_function(home_page);

	register_page_display(home_page);
	register_page_display(keyboard_test_page);
	register_page_display(speaker_test_page);
	register_page_display(led_test_page);
	register_page_display(animation_page);
	register_page_display(new_menu);
}

void set_display_function(const PageDisplay &page_display) {
	current_page = page_display;
	initialized = false;
}

void display_one_frame() {
	if (!initialized) {
		current_page.initialize_function();
		initialized = true;
	}

	if (current_page.function) {
		current_page.function();
	}
}

// 请在 loop() 中调用该函数
void page_controller_loop() {
	display_one_frame();

	if (!is_page_select_key_pressing()) {
		interaction.update_interaction_tick();
	}

	if (interaction.can_interact()) {
		interaction.update_interaction_tick();
		if (page_selectable && current_page != new_menu) {
			set_display_function(new_menu);
		}
	}
}
