//
// Created by qingzhixing on 2025/6/11.
//

#ifndef NEW_PAGE_DISPLAY_HPP
#define NEW_PAGE_DISPLAY_HPP



class NewPageDisplay {
public:
    virtual ~NewPageDisplay() = default;
    virtual void update() = 0;
    virtual void initialize() = 0;
};

#endif //NEW_PAGE_DISPLAY_HPP
