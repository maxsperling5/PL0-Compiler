#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include "../view/IView.hpp"
#include "../data/IData.hpp"

namespace pl0compiler { namespace comp {

class IComp;
typedef std::shared_ptr<IComp> ICompPtr;

class IComp
{
public:
    virtual ~IComp(){}

    virtual bool init(pl0compiler::view::IViewPtr viewPtr, pl0compiler::data::IDataPtr dataPtr) = 0;
    virtual bool exec(int argc, char *argv[]) = 0;
};

} }
