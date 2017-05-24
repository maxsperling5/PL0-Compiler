/************************/
/* Author: Max Sperling */
/************************/

#include "ViewCLI.hh"

#include <iostream>
#include <iomanip>

using namespace std;

IViewPtr IView::create()
{
    return IViewPtr(new ViewCLI());
}

void ViewCLI::write(string str)
{
    cout << endl;
    cout << "---------------------------" << endl;
    cout << "Write string:" << endl;
    cout << endl;
    cout << str;
    cout << endl;
    cout << "---------------------------" << endl;
}

void ViewCLI::write(vector<char> bin)
{
    cout << endl;
    cout << "---------------------------" << endl;
    cout << "Write binary:" << endl;
    cout << endl;
    for(auto &b : bin)
    {
        cout << setfill('0') << setw(2) << hex << +b;
    }
    cout << endl;
    cout << "---------------------------" << endl;
}
