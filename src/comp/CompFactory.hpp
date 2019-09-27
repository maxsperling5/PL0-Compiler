#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IComp.hpp"

enum CompType
{
    PL0
};

class CompFactory
{
public:
    static ICompPtr create(CompType type);
};