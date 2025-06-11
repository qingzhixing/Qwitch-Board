#pragma once
#ifndef SPEAKER_TEST_PAGE_HPP
#define SPEAKER_TEST_PAGE_HPP

#include <page_display.hpp>

#include <NewPageDisplay.hpp>

extern PageDisplay speaker_test_page;

void speaker_test_page_initialize();
void speaker_test_page_update();

class SpeakerTestPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif //! SPEAKER_TEST_PAGE_HPP
