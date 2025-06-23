//
// Created by qingzhixing on 2025/6/6.
//

#ifndef BOARD_CHARACTERISTIC_CALLBACKS_HPP
#define BOARD_CHARACTERISTIC_CALLBACKS_HPP
#include <BLECharacteristic.h>


class BoardCharacteristicCallbacks final : public BLECharacteristicCallbacks
{
public:
    void onRead(BLECharacteristic* pCharacteristic) override {
        // Serial.println("Read request");
    };
    void onWrite(BLECharacteristic* pCharacteristic) override {
        // Serial.println("Write request");
    };
    void onNotify(BLECharacteristic* pCharacteristic) override {
        // Serial.println("On Notify");
    };
};


#endif // BOARD_CHARACTERISTIC_CALLBACKS_HPP
