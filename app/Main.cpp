/************************/
/* Author: Max Sperling */
/************************/

#include "../src/view/ViewFactory.hpp"
#include "../src/data/DataFactory.hpp"
#include "../src/comp/CompFactory.hpp"

int main(int argc, char *argv[])
{
    pl0compiler::view::IViewPtr viewPtr = pl0compiler::view::ViewFactory::create(pl0compiler::view::ViewType::CLI);
    pl0compiler::data::IDataPtr dataPtr = pl0compiler::data::DataFactory::create(pl0compiler::data::DataType::File);
    pl0compiler::comp::ICompPtr compPtr = pl0compiler::comp::CompFactory::create(pl0compiler::comp::CompType::PL0);

    if(!compPtr->init(viewPtr, dataPtr)) return 1;
    if(!compPtr->exec(argc, argv)) return 2;

    return 0;
}
