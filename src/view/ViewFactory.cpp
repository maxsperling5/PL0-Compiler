/************************/
/* Author: Max Sperling */
/************************/

#include "ViewFactory.hpp"
#include "view_cli/ViewCLI.hpp"

using namespace std;

IViewPtr ViewFactory::create(ViewType type)
{
    IViewPtr viewPtr;
    switch(type)
    {
    case ViewType::CLI:
        viewPtr = make_shared<ViewCLI>();
        break;
    }
    return viewPtr;
}