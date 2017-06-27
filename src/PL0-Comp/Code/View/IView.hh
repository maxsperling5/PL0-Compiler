#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <string>
#include <deque>

class IView;
typedef std::shared_ptr<IView> IViewPtr;

class IView
{
public:
    static IViewPtr create();
    virtual ~IView(){}

    virtual void write(std::string str) = 0;
    virtual void write(std::deque<char> bin) = 0;
};
