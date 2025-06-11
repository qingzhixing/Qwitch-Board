#pragma once
#ifndef LED_TEST_PAGE_HPP
#define LED_TEST_PAGE_HPP
#include <page_display.hpp>
#include <NewPageDisplay.hpp>

extern PageDisplay led_test_page;

void led_test_page_init();
void led_test_page_update();

class LedTestPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};
#endif //! LED_TEST_PAGE_HPP
