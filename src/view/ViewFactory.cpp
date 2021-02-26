/************************/
/* Author: Max Sperling */
/************************/

#include "ViewFactory.hpp"
#include "cli/ViewCLI.hpp"

namespace pl0compiler { namespace view {

IViewUPtr ViewFactory::create(ViewType type)
{
    IViewUPtr viewUPtr;
    switch(type)
    {
    case ViewType::CLI:
        viewUPtr.reset(new cli::ViewCLI());
        break;
    }
    return viewUPtr;
}

} }
