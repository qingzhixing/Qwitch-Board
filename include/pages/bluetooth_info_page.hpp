//
// Created by qingzhixing on 2025/6/10.
//

#ifndef BLUETOOTH_INFO_PAGE_HPP
#define BLUETOOTH_INFO_PAGE_HPP

#include <page_display.hpp>

#include <NewPageDisplay.hpp>
extern PageDisplay bluetooth_info_page;

void bluetooth_info_page_init();
void bluetooth_info_page_update();

class BluetoothInfoPage final : public NewPageDisplay
{
public:
    void update() override;
    void initialize() override;
};

#endif // BLUETOOTH_INFO_PAGE_HPP
