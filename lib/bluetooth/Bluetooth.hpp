//
// Created by qingzhixing on 2025/6/5.
//

#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP
#include <BLEDevice.h>


class Bluetooth {
public:
    static bool device_connected;
    static BLEServer* pServer;
    static BLEService* batteryService;
    static BLECharacteristic* systemIdCharacteristic;
public:
    static void init();
    static void update();
};



#endif //BLUETOOTH_HPP
