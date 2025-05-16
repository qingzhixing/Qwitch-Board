//
// Created by qingzhixing on 2025/5/16.
//

#include "pages/game_2048.hpp"
#include <nvs_controller.hpp>
#include <oled.hpp>
#include <interaction.hpp>

PageDisplay game_2048 = PageDisplay("2048", game_2048_init, game_2048_update, icon_2048_bits);

static int max_score = 0;
static int score = 0;
static int game_map[4][4] = {};
static bool in_game = false;

static Interaction interaction(300);

static void read_data() {
    prefs.begin(NVS_NAMESPACE, true);
    max_score = prefs.getInt("2048_score", 0);
    prefs.end();
}

static void save_data() {
    prefs.begin(NVS_NAMESPACE, false);
    prefs.putInt("2048_score", max_score);
    prefs.end();
}

static void generate_number() {
}

static bool game_over_check() {
    return true;
}

void game_2048_init() {
    read_data();
    interaction.update_interaction_tick();
    interaction.add_cooldown(500);
}

static void input_handler() {
}

static void game_logic() {
}

static void display_handler() {
    oled.clearBuffer();
    oled.drawStr(36, 30, "2048");
    oled.sendBuffer();
}

void game_2048_update() {
    input_handler();
    game_logic();
    display_handler();
}
