#pragma once
#ifndef HOME_PAGE_HPP
#define HOME_PAGE_HPP

#include <NewPageDisplay.hpp>

extern NewPageDisplay* home_page;

// Home Page
void home_page_update();
void home_page_initialize();

class HomePage final: public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif //! HOME_PAGE_HPP
