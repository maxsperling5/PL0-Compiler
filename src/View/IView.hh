#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <string>
#include <vector>

class IView;
typedef std::shared_ptr<IView> IViewPtr;

class IView
{
public:
    static IViewPtr create();
    virtual ~IView(){}

    virtual void write(std::string str) = 0;
    virtual void write(std::vector<char> bin) = 0;
};
