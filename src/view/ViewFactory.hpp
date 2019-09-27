#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IView.hpp"

enum ViewType
{
    CLI
};

class ViewFactory
{
public:
    static IViewPtr create(ViewType type);
};