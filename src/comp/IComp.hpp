#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../view/IView.hpp"
#include "../data/IData.hpp"

#include <memory>

namespace pl0compiler { namespace comp {

class IComp;
typedef std::unique_ptr<IComp> ICompUPtr;

class IComp
{
public:
    virtual ~IComp(){}

    virtual bool init(pl0compiler::view::IViewUPtr viewUPtr, pl0compiler::data::IDataUPtr dataUPtr) = 0;
    virtual bool exec(int argc, char *argv[]) = 0;
};

} }
