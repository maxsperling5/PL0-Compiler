/************************/
/* Author: Max Sperling */
/************************/

#include "../src/view/IView.hpp"
#include "../src/data/IData.hpp"
#include "../src/comp/IComp.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    IViewPtr viewPtr = IView::create();
    IDataPtr dataPtr = IData::create();
    ICompPtr compPtr = IComp::create();

    if(!compPtr->init(viewPtr, dataPtr)) return 1;
    if(!compPtr->exec(argc, argv)) return 2;

    return 0;
}
