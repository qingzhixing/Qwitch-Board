//
// Created by qingzhixing on 2025/6/4.
//

#ifndef GAME_2048_SCORE_PAGE_HPP
#define GAME_2048_SCORE_PAGE_HPP
#include "NewPageDisplay.hpp"

extern NewPageDisplay* game_2048_score;

void game_2048_score_page_init();
void game_2048_score_page_update();

class Game2048ScorePage final: public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
};

#endif //GAME_2048_SCORE_PAGE_HPP
