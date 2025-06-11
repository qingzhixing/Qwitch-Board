#pragma once
#ifndef KEYBOARD_TEST_PAGE_HPP
#define KEYBOARD_TEST_PAGE_HPP

#include <page_display.hpp>

#include <NewPageDisplay.hpp>

extern PageDisplay keyboard_test_page;

// Keyboard Test Page
void keyboard_test_page_update();
void keyboard_test_page_initialize();

class KeyboardTestPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif //! KEYBOARD_TEST_PAGE_HPP
