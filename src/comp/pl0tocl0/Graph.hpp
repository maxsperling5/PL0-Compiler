#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <array>

#include "ILGen.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

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

        Trans(Type type, const void *value, int idxNext, int idxAlter, func funct);

        Type m_type;
        const void *m_value;
        unsigned int m_idxNext;
        unsigned int m_idxAlter;
        func m_funct;
    };

    static std::array<Trans,4> m_program;
    static std::array<Trans,21> m_block;
    static std::array<Trans,26> m_statement;
    static std::array<Trans,11> m_condition;
    static std::array<Trans,8> m_expression;
    static std::array<Trans,7> m_term;
    static std::array<Trans,6> m_factor;
};

} } }
