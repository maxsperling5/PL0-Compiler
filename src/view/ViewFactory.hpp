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
    static IViewUPtr create(ViewType type);
};

} }
