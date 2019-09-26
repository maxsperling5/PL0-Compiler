#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IView.hpp"

class ViewCLI : public IView
{
public:
    ViewCLI(){}
    ~ViewCLI(){}

    // --- IView -----------------------------------
    virtual void write(std::string str);
    virtual void write(std::deque<char> bin);
    // ---------------------------------------------
};
