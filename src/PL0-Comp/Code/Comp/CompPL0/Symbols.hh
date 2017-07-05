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
        enum Type
        {
            Proc, Var, Cons
        };

        int m_index;

        virtual ~Object(){};
        virtual Type getType() = 0;
    };

    struct Symbol
    {
        std::string m_name;
        int m_procIdx;
        Object *m_object;

        Symbol(std::string name, int procIdx);
    };

    struct Procedure : Object
    {
        Procedure *m_parent;
        std::vector<Symbol> m_symbolTab;
        int m_numVar;

        Procedure(Procedure *parent, int index);
        ~Procedure(){}
        Type getType();
    };

    struct Variable : Object
    {
        Variable(int index);
        ~Variable(){}
        Type getType();
    };

    struct Constant : Object
    {
        long m_value;

        Constant(long value, int index);
        ~Constant(){}
        Type getType();
    };

    unsigned int m_numProc;
    Procedure *m_curProc;
    std::vector<long> m_vecConst;

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
