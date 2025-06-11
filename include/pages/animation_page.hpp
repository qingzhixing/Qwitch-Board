#pragma once
#ifndef ANIMATION_PAGE_HPP
#define ANIMATION_PAGE_HPP

#include <page_display.hpp>

#include "NewPageDisplay.hpp"
extern PageDisplay animation_page;

void animation_page_initialize();
void animation_page_update();

class AnimationPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif //! ANIMATION_PAGE_HPP
