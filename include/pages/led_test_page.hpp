#pragma once
#ifndef LED_TEST_PAGE_HPP
#define LED_TEST_PAGE_HPP

#include <NewPageDisplay.hpp>

extern NewPageDisplay* led_test_page;

void led_test_page_init();
void led_test_page_update();

class LEDTestPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};
#endif //! LED_TEST_PAGE_HPP
