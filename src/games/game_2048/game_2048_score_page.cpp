//
// Created by qingzhixing on 2025/6/4.
//
#include <games/game_2048/game_2048_score_page.hpp>

#include <games/game_2048/Game2048Page.hpp>
#include <interaction.hpp>
#include <keyboard.hpp>
#include <oled.hpp>
#include <page_controller.hpp>

static Interaction interaction(300);

NewPageDisplay* game_2048_score = new Game2048ScorePage();
void game_2048_score_page_init()
{
    interaction.update_interaction_tick();
    interaction.add_cooldown(200);

    oled.clearBuffer();
    oled.drawStr(15, 18, String("Score: " + String(game_2048_instance.score)).c_str());
    oled.drawStr(15, 38, String("Max Score: " + String(game_2048_instance.max_score)).c_str());
    oled.drawStr(15, 58, "[A] Back");
    oled.sendBuffer();
}
void game_2048_score_page_update()
{
    if (is_key_on_pressed(KEY_A) || (is_key_pressing(KEY_A) && interaction.can_interact()))
    {
        interaction.update_interaction_tick();
        set_new_display_function(game_2048_page);
    }
}

void Game2048ScorePage::update() const { game_2048_score_page_update(); }
void Game2048ScorePage::initialize() const { game_2048_score_page_init(); }
