#pragma once
#ifndef NEW_MENU_HPP
#define NEW_MENU_HPP


#include <NewPageDisplay.hpp>

#define MENU_PAGE_NAME "Menu"

extern NewPageDisplay* menu_page;

void menu_initialize();
void menu_update();

class MenuPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif //! NEW_MENU_HPP
