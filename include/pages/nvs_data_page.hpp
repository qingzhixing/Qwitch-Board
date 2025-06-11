//
// Created by qingzhixing on 2025/5/15.
//
#pragma once
#ifndef NVS_DATA_HPP
#define NVS_DATA_HPP

#include <Preferences.h>

#include <NewPageDisplay.hpp>
#include "page_display.hpp"

extern PageDisplay nvs_data_page;

void nvs_data_page_init();
void nvs_data_page_update();

class NVSDataPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif // NVS_DATA_HPP
