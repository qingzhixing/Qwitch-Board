#pragma once

#ifndef _PAGE_CONTROLLER_
#define _PAGE_CONTROLLER_

#include <keyboard.hpp>
#include <Arduino.h>

typedef void (*DisplayFunction)(void);
typedef void (*InitializeFunction)(void);

class PageDisplay
{
public:
	const char *page_name;
	DisplayFunction function;
	InitializeFunction initialize_function;

	PageDisplay(const char *page_name, DisplayFunction function, InitializeFunction initialize_function)
	{
		this->page_name = page_name;
		this->function = function;
		this->initialize_function = initialize_function;
	}
};

// 传入要在循环中每次调用的函数，以及其初始化函数, 初始化函数仅在第一次调用时调用一次
void set_display_function(DisplayFunction function, InitializeFunction initialize_function);

extern DisplayFunction current_function;

extern bool page_selectable;

inline bool is_page_select_key_pressing()
{
	return is_key_pressing(KEY_A) && is_key_pressing(KEY_B);
}

// 调用之前请先进行好初始化
// void display_one_frame(void);

// 请在 loop() 中调用该函数
void page_controller_loop(void);
void page_controller_init(void);

// 页面选择
void page_select_function(void);
void page_select_initialize(void);
void register_page_display(PageDisplay &&page_display);

#endif // !_PAGE_CONTROLLER_