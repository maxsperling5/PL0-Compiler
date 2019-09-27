/************************/
/* Author: Max Sperling */
/************************/

#include "../src/view/view_cli/ViewCLI.hpp"
#include "../src/data/data_file/DataFile.hpp"
#include "../src/comp/comp_pl0/CompPL0.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    IViewPtr viewPtr(new ViewCLI());
    IDataPtr dataPtr(new DataFile());
    ICompPtr compPtr(new CompPL0());

    if(!compPtr->init(viewPtr, dataPtr)) return 1;
    if(!compPtr->exec(argc, argv)) return 2;

    return 0;
}
