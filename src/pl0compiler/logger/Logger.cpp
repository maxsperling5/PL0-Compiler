/************************/
/* Author: Max Sperling */
/************************/

#include "Logger.hpp"

#include <iostream>
#include <iomanip>

namespace pl0compiler { namespace logger {

void Logger::write(std::string str)
{
    std::cout << str << std::endl;
}

void Logger::write(std::deque<char> bin)
{
    for (auto &b : bin)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << +b;
    }
    std::cout << std::endl;
}

} }
