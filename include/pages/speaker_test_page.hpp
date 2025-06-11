#pragma once
#ifndef SPEAKER_TEST_PAGE_HPP
#define SPEAKER_TEST_PAGE_HPP



#include <NewPageDisplay.hpp>

extern NewPageDisplay* speaker_test_page;

void speaker_test_page_initialize();
void speaker_test_page_update();

class SpeakerTestPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif //! SPEAKER_TEST_PAGE_HPP
