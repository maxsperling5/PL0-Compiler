/************************/
/* Author: Max Sperling */
/************************/

#include "ViewCLI.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

void
pl0compiler::view::cli::ViewCLI::write(string str)
{
    cout << str << endl;
}

void
pl0compiler::view::cli::ViewCLI::write(deque<char> bin)
{
    for(auto &b : bin)
    {
        cout << setfill('0') << setw(2) << hex << +b;
    }
    cout << endl;
}
