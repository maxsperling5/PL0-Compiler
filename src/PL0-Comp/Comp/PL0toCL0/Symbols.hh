#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <vector>

class Symbols
{
public:
    struct Object
    {
        enum Typ
        {
            Proc,
            Var,
            Cons
        };

        int index;

        virtual ~Object(){};
        virtual Typ getType() = 0;
    };

    struct Symbol
    {
        std::string name;
        int procIdx;
        Object *object;

        Symbol(std::string name, int procIdx)
        {
            this->name = name;
            this->procIdx = procIdx;
        }
    };

    struct Procedure : Object
    {
        Procedure *parent;
        std::vector<Symbol> symbolTab;
        int numVar;

        Procedure(Procedure *parent, int index)
        {
            this->parent = parent;
            this->index = index;
            numVar = 0;
        }
        ~Procedure(){};

        Typ getType()
        {
            return Proc;
        }
    };

    struct Variable : Object
    {
        Variable(int index)
        {
            this->index = index;
        }
        ~Variable(){};

        Typ getType()
        {
            return Var;
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
        ~Constant(){}

        Typ getType()
        {
            return Cons;
        }
    };

    unsigned int numProc;
    Procedure *curProc;
    std::vector<long> vecConst;

public:
    Symbols();
    ~Symbols();

    void addSymbol(std::string name);
    void addProcedure();
    void retProcedure();
    void delProcedure(Procedure *proc);
    void addVariable();
    void addConstant(long value);
    void addConstNum(long value);
    int getCurProcIdx();
    int getCurProcNumVar();
    Symbol *searchSymb(std::string name);
};
