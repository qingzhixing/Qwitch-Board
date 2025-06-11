#pragma once
#ifndef NEW_MENU_HPP
#define NEW_MENU_HPP
#include <page_display.hpp>

#include <NewPageDisplay.hpp>

extern PageDisplay menu_page;

void menu_initialize();
void menu_update();

class MenuPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif //! NEW_MENU_HPP
