/************************/
/* Author: Max Sperling */
/************************/

#include "ViewFactory.hpp"
#include "cli/ViewCLI.hpp"

using namespace std;

namespace pl0compiler { namespace view {

pl0compiler::view::IViewPtr
pl0compiler::view::ViewFactory::create(ViewType type)
{
    IViewPtr viewPtr;
    switch(type)
    {
    case ViewType::CLI:
        viewPtr = make_shared<cli::ViewCLI>();
        break;
    }
    return viewPtr;
}

} }
