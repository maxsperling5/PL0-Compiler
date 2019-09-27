/************************/
/* Author: Max Sperling */
/************************/

#include "../src/view/ViewFactory.hpp"
#include "../src/data/DataFactory.hpp"
#include "../src/comp/CompFactory.hpp"

int main(int argc, char *argv[])
{
    IViewPtr viewPtr = ViewFactory::create(ViewType::CLI);
    IDataPtr dataPtr = DataFactory::create(DataType::File);
    ICompPtr compPtr = CompFactory::create(CompType::PL0);

    if(!compPtr->init(viewPtr, dataPtr)) return 1;
    if(!compPtr->exec(argc, argv)) return 2;

    return 0;
}
