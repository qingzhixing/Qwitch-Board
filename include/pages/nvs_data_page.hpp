//
// Created by qingzhixing on 2025/5/15.
//
#pragma once
#ifndef NVS_DATA_HPP
#define NVS_DATA_HPP

#include <Preferences.h>

#include <NewPageDisplay.hpp>


extern NewPageDisplay* nvs_data_page;

void nvs_data_page_init();
void nvs_data_page_update();

class NVSDataPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif // NVS_DATA_HPP
