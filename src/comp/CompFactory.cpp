/************************/
/* Author: Max Sperling */
/************************/

#include "CompFactory.hpp"
#include "comp_pl0/CompPL0.hpp"

using namespace std;

ICompPtr CompFactory::create(CompType type)
{
    ICompPtr compPtr;
    switch(type)
    {
    case CompType::PL0:
        compPtr = make_shared<CompPL0>();
        break;
    }
    return compPtr;
}