//
// Created by qingzhixing on 2025/6/10.
//

#ifndef BLUETOOTH_INFO_PAGE_HPP
#define BLUETOOTH_INFO_PAGE_HPP



#include <NewPageDisplay.hpp>
extern NewPageDisplay* bluetooth_info_page;

void bluetooth_info_page_init();
void bluetooth_info_page_update();

class BluetoothInfoPage final : public NewPageDisplay
{
public:
    void update() const override;
    void initialize() const override;
    std::string get_name() const override;
    const unsigned char* get_icon() const override;
};

#endif // BLUETOOTH_INFO_PAGE_HPP
