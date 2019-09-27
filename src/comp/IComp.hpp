#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include "../view/IView.hpp"
#include "../data/IData.hpp"

class IComp;
typedef std::shared_ptr<IComp> ICompPtr;

class IComp
{
public:
    virtual ~IComp(){}

    virtual bool init(IViewPtr viewPtr, IDataPtr dataPtr) = 0;
    virtual bool exec(int argc, char *argv[]) = 0;
};
