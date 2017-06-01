/************************/
/* Author: Max Sperling */
/************************/

#include "Symbols.hh"

using namespace std;

Symbols::Symbol::Symbol(string name, int procIdx)
{
    this->name = name;
    this->procIdx = procIdx;
}

Symbols::Procedure::Procedure(Procedure *parent, int index)
{
    this->parent = parent;
    this->index = index;
    numVar = 0;
}

Symbols::Object::Typ Symbols::Procedure::getType()
{
    return Proc;
}

Symbols::Variable::Variable(int index)
{
    this->index = index;
}

Symbols::Object::Typ Symbols::Variable::getType()
{
    return Var;
}

Symbols::Constant::Constant(long value, int index)
{
    this->value = value;
    this->index = index;
}

Symbols::Object::Typ Symbols::Constant::getType()
{
    return Cons;
}

Symbols::Symbols()
{
    numProc = 0;
    curProc = nullptr;
    addProcedure();
}

Symbols::~Symbols()
{
    while(curProc->parent != nullptr)
    {
        curProc = curProc->parent;
    }

    delProcedure(curProc);
    delete curProc;
}

void Symbols::addSymbol(string name)
{
    Symbol symb(name, curProc->index);
    curProc->symbolTab.push_back(symb);
}

void Symbols::addProcedure()
{
    Procedure *proc = new Procedure(curProc, numProc);
    if(curProc != nullptr)
    {
        curProc->symbolTab.back().object = proc;
    }
    curProc = proc;
    numProc++;
}

void Symbols::retProcedure()
{
    curProc = curProc->parent;
}

void Symbols::delProcedure(Procedure *proc)
{
    for(Symbol &symb : proc->symbolTab)
    {
        if(symb.object->getType() == Symbols::Object::Proc)
            delProcedure((Procedure*)symb.object);
        delete symb.object;
    }
}

void Symbols::addVariable()
{
    Variable *var = new Variable(curProc->numVar);
    curProc->symbolTab.back().object = var;
    curProc->numVar++;
}

void Symbols::addConstant(long value)
{
    Constant *cons = new Constant(value, vecConst.size());
    curProc->symbolTab.back().object = cons;
    vecConst.push_back(value);
}

void Symbols::addConstNum(long value)
{
    vecConst.push_back(value);
}

int Symbols::getCurProcIdx()
{
    return curProc->index;
}

int Symbols::getCurProcNumVar()
{
    return curProc->numVar;
}

Symbols::Symbol *Symbols::searchSymb(string name)
{
    Procedure *tmpProc = curProc;

    while(tmpProc != nullptr)
    {
        for(Symbol &symb : tmpProc->symbolTab)
        {
            if(symb.name == name)
                return &symb;
        }
        tmpProc = tmpProc->parent;
    }

    return nullptr;
}
