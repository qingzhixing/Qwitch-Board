//
// Created by qingzhixing on 2025/5/16.
//

#include "pages/game_2048_page.hpp"
#include <interaction.hpp>
#include <nvs_controller.hpp>
#include <oled.hpp>

#include "../../include/Coord.h"

PageDisplay game_2048 = PageDisplay("2048", game_2048_page_init, game_2048_update, icon_2048_bits);

static int max_score = 0;
static int score = 0;
static int game_map[4][4] = {};
static bool in_game = false;

static Interaction interaction(300);

static void read_data()
{
    prefs.begin(NVS_NAMESPACE, true);
    max_score = prefs.getInt("2048_score", 0);
    prefs.end();
}

static void save_data()
{
    prefs.begin(NVS_NAMESPACE, false);
    prefs.putInt("2048_score", max_score);
    prefs.end();
}

static void generate_number()
{

}

static bool game_over_check() { return true; }

static void new_game_init() { memset(game_map, 0, sizeof(game_map)); }

void game_2048_page_init()
{
    read_data();

    if (!in_game)
    {
        new_game_init();
        in_game = true;
    }

    interaction.update_interaction_tick();
    interaction.add_cooldown(500);
}

static void input_handler() {}

static void game_logic() {}

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
            if (game_map[i][j] != 0)
            {
                const char buf[10] = {static_cast<char>('0' + game_map[i][j]), '\0'};
                oled.drawStr(coord.x, coord.y, buf);
            }
        }
    }
    oled.sendBuffer();
}

void game_2048_update()
{
    input_handler();
    game_logic();
    display_handler();
}
