#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include "../View/IView.hh"
#include "../Data/IData.hh"

class IComp;
typedef std::shared_ptr<IComp> ICompPtr;

class IComp
{
public:
    static ICompPtr create();
    virtual ~IComp(){}

    virtual bool init(IViewPtr viewPtr, IDataPtr dataPtr) = 0;
    virtual bool exec(int argc, char *argv[]) = 0;
};
