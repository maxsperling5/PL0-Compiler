#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IView.hpp"

namespace pl0compiler { namespace view {

enum ViewType
{
    CLI
};

class ViewFactory
{
public:
    static IViewPtr create(ViewType type);
};

} }
