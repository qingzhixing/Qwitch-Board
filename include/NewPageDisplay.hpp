//
// Created by qingzhixing on 2025/6/11.
//

#ifndef NEW_PAGE_DISPLAY_HPP
#define NEW_PAGE_DISPLAY_HPP
#include <string>

#include "bitmaps.hpp"

class NewPageDisplay
{
public:
    virtual ~NewPageDisplay() = default;
    virtual void update() const = 0;
    virtual void initialize() const = 0;
    virtual std::string get_name() const { return "Unnamed Page"; };
    virtual const unsigned char* get_icon() const { return icon_smile_bits; };
};

#endif // NEW_PAGE_DISPLAY_HPP
