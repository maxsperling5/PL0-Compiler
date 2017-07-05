#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <array>
class ILGen;

class Graph
{
public:
    typedef void (ILGen::*func)(void*);

    struct Trans
    {
        enum Type
        {
            Nil, Symbol, Token, GraphStart, GraphEnd
        };

        Trans(){}
        Trans(Type type, const void *value, int idxNext, int idxAlter, func funct);

        Type m_type;
        const void *m_value;
        unsigned int m_idxNext;
        unsigned int m_idxAlter;
        func m_funct;
    };

public:
    Graph();

    std::array<Trans,4> m_program;
    std::array<Trans,21> m_block;
    std::array<Trans,26> m_statement;
    std::array<Trans,11> m_condition;
    std::array<Trans,8> m_expression;
    std::array<Trans,7> m_term;
    std::array<Trans,6> m_factor;
};
