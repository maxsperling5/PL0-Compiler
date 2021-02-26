/************************/
/* Author: Max Sperling */
/************************/

#include "CompFactory.hpp"
#include "pl0tocl0/CompPL0.hpp"

using namespace std;

pl0compiler::comp::ICompUPtr
pl0compiler::comp::CompFactory::create(CompType type)
{
    ICompUPtr compUPtr;
    switch(type)
    {
    case CompType::PL0:
        compUPtr.reset(new pl0tocl0::CompPL0());
        break;
    }
    return compUPtr;
}
