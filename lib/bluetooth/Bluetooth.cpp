//
// Created by qingzhixing on 2025/6/5.
//

#include "Bluetooth.hpp"
#include <Arduino.h>
#include <BLEDevice.h>

#include "BoardCharacteristicCallbacks.hpp"
#include "BoardServerCallbacks.hpp"

// Define static member variables
bool Bluetooth::device_connected = false;
BLEServer* Bluetooth::pServer = nullptr;
BLEService* Bluetooth::batteryService = nullptr;
BLECharacteristic* Bluetooth::systemIdCharacteristic = nullptr;

#define BLUETOOTH_BATTERY_SERVICE_UUID                                                                                 \
    "0000180F-0000-1000-8000-00805F9B34FB" // 0x180F是蓝牙技术联盟定义的Battery Service的16-bit UUID
#define SYSTEM_ID_CHARACTERISTIC_UUID                                                                                  \
    "00002A23-0000-1000-8000-00805F9B34FB" // 0x2A23是蓝牙技术联盟定义的System ID Characteristic的16-bit UUID

void Bluetooth::init()
{
    BLEDevice::init("Qwitch Board");

    pServer = BLEDevice::createServer();

    const auto callbacks = new BoardServerCallbacks();
    callbacks->connection_hook = []() { device_connected = true; };
    callbacks->disconnection_hook = []() { device_connected = false; };

    pServer->setCallbacks(callbacks);

    batteryService = pServer->createService(BLUETOOTH_BATTERY_SERVICE_UUID);

    systemIdCharacteristic = batteryService->createCharacteristic(
        SYSTEM_ID_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    // 设置System ID的值
    systemIdCharacteristic->setValue("0x55aa");
    systemIdCharacteristic->setCallbacks(new BoardCharacteristicCallbacks());

    // 添加客户端特征配置描述符（Client Characteristic Configuration Descriptor）
    // 用于客户端配置通知和指示
    const auto pClientConfigDescriptor = new BLEDescriptor(
        BLEUUID(static_cast<uint16_t>(0x2902)), // 0x2902 是蓝牙技术联盟定义的客户端特征配置描述符的 UUID
        2 // 最大长度为 2 字节，用于存储通知和指示的使能状态
    );
    systemIdCharacteristic->addDescriptor(pClientConfigDescriptor);

    // 添加特征用户描述符（Characteristic User Description Descriptor）
    // 用于为特征提供用户可读的描述信息
    const auto pUserDescDescriptor =
        new BLEDescriptor(BLEUUID(static_cast<uint16_t>(0x2901)), // 0x2901 是蓝牙技术联盟定义的特征用户描述符的 UUID
                          20 // 最大长度为 20 字节，可根据实际描述长度调整
        );
    pUserDescDescriptor->setValue("System ID Characteristic"); // 设置描述信息

    systemIdCharacteristic->addDescriptor(pUserDescDescriptor);

    batteryService->start();

    BLEDevice::startAdvertising();
}
void Bluetooth::update()
{
    if (device_connected)
    {
        static unsigned long last_notify_time;
        if (millis() - last_notify_time > 1000)
        {
            last_notify_time = millis();
            systemIdCharacteristic->setValue("Hello, Qwitch!");
            systemIdCharacteristic->notify();
        }
    }
}
