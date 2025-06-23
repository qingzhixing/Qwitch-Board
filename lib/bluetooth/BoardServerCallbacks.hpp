//
// Created by qingzhixing on 2025/6/5.
//

#ifndef BOARD_SERVER_CALLBACKS_HPP
#define BOARD_SERVER_CALLBACKS_HPP
#include <BLEServer.h>
#include <HardwareSerial.h>


class BoardServerCallbacks final : public BLEServerCallbacks
{
public:
    typedef void (*hook_t)();

public:
    hook_t connection_hook = nullptr;
    hook_t disconnection_hook = nullptr;

public:
    void onConnect(BLEServer* pServer) override
    {
        if (connection_hook != nullptr)
        {
            connection_hook();
        }
        // 打印消息并打印设备名称
        // Serial.println("设备接入Qwitch Board, 设备ID: " + String(pServer->getConnId()) + "\n");
    };
    void onDisconnect(BLEServer* pServer) override
    {
        if (disconnection_hook != nullptr)
        {
            disconnection_hook();
        }
        // 打印消息并打印设备名称
        // Serial.println("设备断开Qwitch Board, 设备ID: " + String(pServer->getConnId()) + "\n");
        // 重新广播
        pServer->startAdvertising();
    };
};


#endif // BOARD_SERVER_CALLBACKS_HPP
