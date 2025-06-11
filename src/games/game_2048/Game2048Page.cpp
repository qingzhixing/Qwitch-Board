//
// Created by qingzhixing on 2025/5/16.
//

#include <Arduino.h>
#include <Coord.hpp>
#include <games/game_2048/Game2048Page.hpp>
#include <games/game_2048/Game_2048.hpp>
#include <interaction.hpp>
#include <nvs_controller.hpp>
#include <oled.hpp>

#include <keyboard.hpp>
#include <page_controller.hpp>

#include "bitmaps.hpp"
#include "games/game_2048/game_2048_score_page.hpp"

NewPageDisplay* game_2048_page = new Game2048Page();

Game_2048 game_2048_instance{};

static Interaction interaction(300);

static void read_data()
{
    prefs.begin(NVS_NAMESPACE, true);
    game_2048_instance.max_score = prefs.getInt("2048_score", 0);
    prefs.end();
}

static void save_data()
{
    prefs.begin(NVS_NAMESPACE, false);
    prefs.putInt("2048_score", game_2048_instance.max_score);
    prefs.end();
}

void game_2048_page_init()
{
    read_data();

    if (!game_2048_instance.in_game)
    {
        game_2048_instance.start_new_game();
    }

    interaction.update_interaction_tick();
    interaction.add_cooldown(500);
}

static void input_handler()
{
    if (is_page_select_key_pressing())
        return;
    if (is_key_on_pressed(KEY_A) || (is_key_pressing(KEY_A) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        // 显示分数
        set_new_display_function(game_2048_score);
        return;
    }
    if (is_key_on_pressed(KEY_UP) || (is_key_pressing(KEY_UP) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        game_2048_instance.do_game_input(UP);
        return;
    }
    if (is_key_on_pressed(KEY_DOWN) || (is_key_pressing(KEY_DOWN) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        game_2048_instance.do_game_input(DOWN);
        return;
    }
    if (is_key_on_pressed(KEY_LEFT) || (is_key_pressing(KEY_LEFT) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        game_2048_instance.do_game_input(LEFT);
        return;
    }
    if (is_key_on_pressed(KEY_RIGHT) || (is_key_pressing(KEY_RIGHT) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        game_2048_instance.do_game_input(RIGHT);
        return;
    }
}

static void display_handler()
{
    oled.clearBuffer();
    // 绘制固有的内容
    oled.drawXBM(0, 0, 64, 64, boarder_2048_bits);
    oled.drawXBM(65, 1, 61, 17, text_2048_boarder_bits);
    oled.setFont(TEXT_NORMAL_FONT);
    oled.drawStr(83, 13, "2048");
    oled.drawStr(69, 34, "[A] Score");
    oled.drawStr(69, 53, "[AB] Exit");

    // 绘制地图
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            static Coord first_coord(10, 16);
            const auto coord = first_coord + Coord(13 * j, 13 * i);
            if (game_2048_instance.game_map[i][j] != 0)
            {
                oled.drawStr(coord.x, coord.y, String(game_2048_instance.game_map[i][j]).c_str());
            }
        }
    }
    oled.sendBuffer();
}

void game_2048_page_update()
{
    input_handler();
    display_handler();
    if (game_2048_instance.is_game_over())
    {
        Serial.println("Game over!");
        save_data();
        game_2048_instance.start_new_game();
    }
}

void Game2048Page::update() const { game_2048_page_update(); }

void Game2048Page::initialize() const { game_2048_page_init(); }

std::string Game2048Page::get_name() const { return "2048"; }

const unsigned char* Game2048Page::get_icon() const { return icon_2048_bits; }
