/************************/
/* Author: Max Sperling */
/************************/

#include "CompFactory.hpp"
#include "pl0tocl0/CompPL0.hpp"

using namespace std;

pl0compiler::comp::ICompPtr
pl0compiler::comp::CompFactory::create(CompType type)
{
    ICompPtr compPtr;
    switch(type)
    {
    case CompType::PL0:
        compPtr = make_shared<pl0tocl0::CompPL0>();
        break;
    }
    return compPtr;
}
