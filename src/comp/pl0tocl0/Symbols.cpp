/************************/
/* Author: Max Sperling */
/************************/

#include "Symbols.hpp"

using namespace std;

pl0compiler::comp::pl0tocl0::Symbols::Symbol::Symbol(string name, int procIdx)
{
    m_name = name;
    m_procIdx = procIdx;
}

pl0compiler::comp::pl0tocl0::Symbols::Procedure::Procedure(Procedure *parent, int index)
{
    m_parent = parent;
    m_index = index;
    m_numVar = 0;
}

pl0compiler::comp::pl0tocl0::Symbols::Object::Type
pl0compiler::comp::pl0tocl0::Symbols::Procedure::getType()
{
    return Proc;
}

pl0compiler::comp::pl0tocl0::Symbols::Variable::Variable(int index)
{
    m_index = index;
}

pl0compiler::comp::pl0tocl0::Symbols::Object::Type
pl0compiler::comp::pl0tocl0::Symbols::Variable::getType()
{
    return Var;
}

pl0compiler::comp::pl0tocl0::Symbols::Constant::Constant(long value, int index)
{
    m_value = value;
    m_index = index;
}

pl0compiler::comp::pl0tocl0::Symbols::Object::Type
pl0compiler::comp::pl0tocl0::Symbols::Constant::getType()
{
    return Cons;
}

pl0compiler::comp::pl0tocl0::Symbols::Symbols()
{
    m_numProc = 0;
    m_curProc = nullptr;
    addProcedure();
}

pl0compiler::comp::pl0tocl0::Symbols::~Symbols()
{
    while(m_curProc->m_parent != nullptr)
    {
        m_curProc = m_curProc->m_parent;
    }

    delProcedure(m_curProc);
    delete m_curProc;
}

void
pl0compiler::comp::pl0tocl0::Symbols::addSymbol(string name)
{
    Symbol symb(name, m_curProc->m_index);
    m_curProc->m_symbolTab.push_back(symb);
}

void
pl0compiler::comp::pl0tocl0::Symbols::addProcedure()
{
    Procedure *proc = new Procedure(m_curProc, m_numProc);
    if(m_curProc != nullptr)
    {
        m_curProc->m_symbolTab.back().m_object = proc;
    }
    m_curProc = proc;
    m_numProc++;
}

void
pl0compiler::comp::pl0tocl0::Symbols::retProcedure()
{
    m_curProc = m_curProc->m_parent;
}

void
pl0compiler::comp::pl0tocl0::Symbols::delProcedure(Procedure *proc)
{
    for(Symbol &symb : proc->m_symbolTab)
    {
        if(symb.m_object->getType() == Symbols::Object::Proc)
            delProcedure((Procedure*)symb.m_object);
        delete symb.m_object;
    }
}

void
pl0compiler::comp::pl0tocl0::Symbols::addVariable()
{
    Variable *var = new Variable(m_curProc->m_numVar);
    m_curProc->m_symbolTab.back().m_object = var;
    m_curProc->m_numVar++;
}

void
pl0compiler::comp::pl0tocl0::Symbols::addConstant(long value)
{
    Constant *cons = new Constant(value, m_vecConst.size());
    m_curProc->m_symbolTab.back().m_object = cons;
    m_vecConst.push_back(value);
}

void
pl0compiler::comp::pl0tocl0::Symbols::addConstNum(long value)
{
    m_vecConst.push_back(value);
}

int
pl0compiler::comp::pl0tocl0::Symbols::getCurProcIdx()
{
    return m_curProc->m_index;
}

int
pl0compiler::comp::pl0tocl0::Symbols::getCurProcNumVar()
{
    return m_curProc->m_numVar;
}

pl0compiler::comp::pl0tocl0::Symbols::Symbol *
pl0compiler::comp::pl0tocl0::Symbols::searchSymb(string name)
{
    Procedure *tmpProc = m_curProc;

    while(tmpProc != nullptr)
    {
        for(Symbol &symb : tmpProc->m_symbolTab)
        {
            if(symb.m_name == name)
                return &symb;
        }
        tmpProc = tmpProc->m_parent;
    }

    return nullptr;
}
