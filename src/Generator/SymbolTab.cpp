/************************/
/* Author: Max Sperling */
/************************/

#ifndef SYMBOLTAB
#define SYMBOLTAB

#include <string>
#include <vector>
using namespace std;

class SymbolTab
{
public:
    struct Object
    {
        int index;
    };

    struct Symbol
    {
        string name;
        int procIdx;
        Object *object;

        Symbol(string name, int procIdx)
        {
            this->name = name;
            this->procIdx = procIdx;
        }
    };

    struct Procedure : Object
    {
        Procedure *parent;
        vector<Symbol> symbolTab;
        int numVar;

        Procedure(Procedure *parent, int index)
        {
            this->parent = parent;
            this->index = index;
            numVar = 0;
        }
    };

    struct Variable : Object
    {
        Variable(int index)
        {
            this->index = index;
        }
    };

    struct Constant : Object
    {
        long value;

        Constant(long value, int index)
        {
            this->value = value;
            this->index = index;
        }
    };

    int numProc;
    Procedure *curProc;
    vector<long> vecConst;

public:
    SymbolTab()
    {
        numProc = 0;
        curProc = nullptr;
        addProcedure();
    }

    ~SymbolTab()
    {
        //cleanup
    }

    void addSymbol(string name)
    {
        Symbol symb(name, curProc->index);
        curProc->symbolTab.push_back(symb);
    }

    void addProcedure()
    {
        Procedure *proc = new Procedure(curProc, numProc);
        if(curProc != nullptr)
        {
            curProc->symbolTab.back().object = proc;
        }
        curProc = proc;
        numProc++;
    }

    void retProcedure()
    {
        curProc = curProc->parent;
    }

    void addVariable()
    {
        Variable *var = new Variable(curProc->numVar);
        curProc->symbolTab.back().object = var;
        curProc->numVar++;
    }

    void addConstant(long value)
    {
        Constant *cons = new Constant(value, vecConst.size());
        curProc->symbolTab.back().object = cons;
        vecConst.push_back(value);
    }

    void addConstNum(long value)
    {
        vecConst.push_back(value);
    }

    int getCurProcIdx()
    {
        return curProc->index;
    }

    int getCurProcNumVar()
    {
        return curProc->numVar;
    }

    Symbol *searchSymb(string name)
    {
        Procedure *tmpProc = curProc;

        while(tmpProc != nullptr)
        {
            for(Symbol &symb : curProc->symbolTab)
            {
                if(symb.name == name)
                    return &symb;
            }
            tmpProc = tmpProc->parent;
        }

        return nullptr;
    }
};

#endif
