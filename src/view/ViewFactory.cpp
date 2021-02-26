/************************/
/* Author: Max Sperling */
/************************/

#include "ViewFactory.hpp"
#include "cli/ViewCLI.hpp"

using namespace std;

namespace pl0compiler { namespace view {

pl0compiler::view::IViewUPtr
pl0compiler::view::ViewFactory::create(ViewType type)
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
