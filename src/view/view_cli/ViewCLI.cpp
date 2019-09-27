/************************/
/* Author: Max Sperling */
/************************/

#include "ViewCLI.hpp"

#include <iostream>
#include <iomanip>

void ViewCLI::write(std::string str)
{
    std::cout << str << std::endl;
}

void ViewCLI::write(std::deque<char> bin)
{
    for(auto &b : bin)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << +b;
    }
    std::cout << std::endl;
}
