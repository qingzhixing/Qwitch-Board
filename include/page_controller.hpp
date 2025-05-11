#pragma once

#ifndef _PAGE_CONTROLLER_
#define _PAGE_CONTROLLER_

#include <keyboard.hpp>
#include <Arduino.h>
#include <bitmaps.hpp>
#include <vector>
#include <page_display.hpp>

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_display_function(PageDisplay page_display);

extern bool page_selectable;
extern std::vector<PageDisplay> page_displays;

// 调用之前请先进行好初始化
// void display_one_frame(void);

// 请在 loop() 中调用该函数
void page_controller_loop(void);
void page_controller_init(void);

// 页面选择
void menu_page_function(void);
void menu_page_initialize(void);
void register_page_display(PageDisplay &&page_display);
void register_page_display(const PageDisplay &page_display);

#endif // !_PAGE_CONTROLLER_