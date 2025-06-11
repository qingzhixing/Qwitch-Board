#pragma once
#ifndef HOME_PAGE_HPP
#define HOME_PAGE_HPP

#include <page_display.hpp>

#include <NewPageDisplay.hpp>

extern PageDisplay home_page;

// Home Page
void home_page_update();
void home_page_initialize();

class HomePage final: public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif //! HOME_PAGE_HPP
