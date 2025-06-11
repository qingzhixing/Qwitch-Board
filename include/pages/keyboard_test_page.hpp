#pragma once
#ifndef KEYBOARD_TEST_PAGE_HPP
#define KEYBOARD_TEST_PAGE_HPP



#include <NewPageDisplay.hpp>

extern NewPageDisplay* keyboard_test_page;

// Keyboard Test Page
void keyboard_test_page_update();
void keyboard_test_page_initialize();

class KeyboardTestPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif //! KEYBOARD_TEST_PAGE_HPP
