#pragma once

#ifndef PAGE_CONTROLLER_
#define PAGE_CONTROLLER_

#include <NewPageDisplay.hpp>

#include <vector>

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_new_display_function(const NewPageDisplay* new_page_display);

extern bool page_selectable;
extern std::vector<const NewPageDisplay*> new_page_displays;

// 请在 loop() 中调用该函数
void page_controller_loop();
void page_controller_init();

// 页面选择
void register_new_page_display(const NewPageDisplay* page_display);

#endif // !PAGE_CONTROLLER_
