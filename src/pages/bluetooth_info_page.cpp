//
// Created by qingzhixing on 2025/6/10.
//
#include <pages/bluetooth_info_page.hpp>

#include <Bluetooth.hpp>
#include <oled.hpp>

#include "bitmaps.hpp"

NewPageDisplay* bluetooth_info_page = new BluetoothInfoPage();

void bluetooth_info_page_init() {}

void bluetooth_info_page_update()
{
    oled.clearBuffer();
    oled.drawBox(0, 0, 128, 12);
    oled.setDrawColor(0);
    oled.setFont(TEXT_NORMAL_FONT);
    oled.drawStr(30, 10, "Bluetooth");
    oled.setDrawColor(1);

    oled.drawStr(10, 30, String(Bluetooth::device_connected ? "Connected" : "Disconnected").c_str());

    oled.sendBuffer();
}

void BluetoothInfoPage::update() const { bluetooth_info_page_update(); }
void BluetoothInfoPage::initialize() const { bluetooth_info_page_init(); }
std::string BluetoothInfoPage::get_name() const { return "Bluetooth"; }
const unsigned char* BluetoothInfoPage::get_icon() const { return icon_bluetooth_bits; }
