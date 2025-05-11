#pragma once
#ifndef PAGE_DISPLAY_HPP
#define PAGE_DISPLAY_HPP
#include "bitmaps.hpp"

typedef void (*DisplayFunction)(void);
typedef void (*InitializeFunction)(void);

class PageDisplay
{
public:
	const char *page_name;
	DisplayFunction function;
	InitializeFunction initialize_function;
	const unsigned char *page_icon;

	PageDisplay(const char *page_name, DisplayFunction function, InitializeFunction initialize_function, const unsigned char *page_icon = epd_bitmap_icon_smile)
	{
		this->page_name = page_name;
		this->function = function;
		this->initialize_function = initialize_function;
		this->page_icon = page_icon;
	}
	PageDisplay(DisplayFunction function, InitializeFunction initialize_function)
	{
		this->page_name = "Unnamed Page";
		this->function = function;
		this->initialize_function = initialize_function;
		this->page_icon = epd_bitmap_icon_smile;
	}
	bool operator==(const PageDisplay &other) const
	{
		return function == other.function && initialize_function == other.initialize_function;
	}
	bool operator!=(const PageDisplay &other) const
	{
		return !(*this == other);
	}
};

#endif //! PAGE_DISPLAY_HPP