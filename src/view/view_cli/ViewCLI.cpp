/************************/
/* Author: Max Sperling */
/************************/

#include "ViewCLI.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

IViewPtr IView::create()
{
    return IViewPtr(new ViewCLI());
}

void ViewCLI::write(string str)
{
    cout << str << endl;
}

void ViewCLI::write(deque<char> bin)
{
    for(auto &b : bin)
    {
        cout << setfill('0') << setw(2) << hex << +b;
    }
    cout << endl;
}
