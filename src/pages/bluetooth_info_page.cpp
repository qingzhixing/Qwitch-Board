//
// Created by qingzhixing on 2025/6/10.
//
#include <pages/bluetooth_info_page.hpp>

#include <Bluetooth.hpp>
#include <oled.hpp>

PageDisplay bluetooth_info_page("Bluetooth", bluetooth_info_page_update,bluetooth_info_page_init, icon_bluetooth_bits);

void bluetooth_info_page_init()
{
}

void bluetooth_info_page_update()
{
    oled.clearBuffer();
    oled.drawBox(0,0,128,12);
    oled.setDrawColor(0);
    oled.setFont(TEXT_NORMAL_FONT);
    oled.drawStr(30,10,"Bluetooth");
    oled.setDrawColor(1);

    oled.drawStr(10,30,String(Bluetooth::device_connected ? "Connected" : "Disconnected").c_str());

    oled.sendBuffer();
}

void BluetoothInfoPage::update()
{
    bluetooth_info_page_update();
}
void BluetoothInfoPage::initialize()
{
    bluetooth_info_page_init();
}
