#pragma once
#ifndef ANIMATION_PAGE_HPP
#define ANIMATION_PAGE_HPP
#include <NewPageDisplay.hpp>
extern NewPageDisplay* animation_page;

void animation_page_initialize();
void animation_page_update();

class AnimationPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif //! ANIMATION_PAGE_HPP
