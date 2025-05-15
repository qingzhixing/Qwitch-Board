//
// Created by qingzhixing on 2025/5/15.
//
#pragma once
#ifndef NVS_HPP
#define NVS_HPP
#include <Preferences.h>

void nvs_controller_init();

#define NVS_NAMESPACE "qwitch_board"

extern Preferences prefs;

#endif //NVS_HPP
