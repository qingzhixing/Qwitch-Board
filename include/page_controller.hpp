#pragma once

#ifndef PAGE_CONTROLLER_
#define PAGE_CONTROLLER_

#include <vector>
#include <page_display.hpp>

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_display_function(const PageDisplay &page_display);

extern bool page_selectable;
extern std::vector<PageDisplay> page_displays;

// 请在 loop() 中调用该函数
void page_controller_loop();
void page_controller_init();

// 页面选择
void register_page_display(PageDisplay &&page_display);
void register_page_display(const PageDisplay &page_display);

#endif // !PAGE_CONTROLLER_
