#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IView.hpp"

namespace pl0compiler { namespace view { namespace cli {

class ViewCLI : public IView
{
public:
    // --- IView -----------------------------------
    virtual void write(std::string str);
    virtual void write(std::deque<char> bin);
    // ---------------------------------------------
};

} } }
