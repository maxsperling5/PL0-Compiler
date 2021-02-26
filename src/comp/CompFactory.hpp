#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IComp.hpp"

namespace pl0compiler { namespace comp {

enum CompType
{
    PL0
};

class CompFactory
{
public:
    static ICompUPtr create(CompType type);
};

} }
