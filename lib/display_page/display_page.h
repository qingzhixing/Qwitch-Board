#pragma once

#ifndef DISPLAY_PAGE_H
#define DISPLAY_PAGE_H

typedef void (*DisplayFunction)(void);
typedef void (*InitializeFunction)(void);

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_display_function(DisplayFunction function, InitializeFunction initialize_function);

// 调用之前请先进行好初始化
void display_one_frame(void);

// Home Page
void home_page_function(void);
void home_page_initialize(void);

// Keyboard Test Page
void keyboard_test_page_function(void);
void keyboard_test_page_initialize(void);

#endif // !DISPLAY_PAGE_H