#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <string>
#include <deque>

namespace pl0compiler { namespace view {

class IView;
typedef std::unique_ptr<IView> IViewUPtr;

class IView
{
public:
    virtual ~IView(){}

    virtual void write(std::string str) = 0;
    virtual void write(std::deque<char> bin) = 0;
};

} }
