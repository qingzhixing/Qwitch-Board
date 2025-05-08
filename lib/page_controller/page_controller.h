#pragma once

#ifndef _PAGE_CONTROLLER_
#define _PAGE_CONTROLLER_

typedef void (*DisplayFunction)(void);
typedef void (*InitializeFunction)(void);

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_display_function(DisplayFunction function, InitializeFunction initialize_function);

extern DisplayFunction current_function;

extern bool page_selectable;

// 调用之前请先进行好初始化
// void display_one_frame(void);

// 请在 loop() 中调用该函数
void page_controller_loop(void);
void page_controller_init(void);

// 页面选择函数
void page_select_function(void);
void page_select_initialize(void);

// Home Page
void home_page_function(void);
void home_page_initialize(void);

// Keyboard Test Page
void keyboard_test_page_function(void);
void keyboard_test_page_initialize(void);

#endif // !_PAGE_CONTROLLER_