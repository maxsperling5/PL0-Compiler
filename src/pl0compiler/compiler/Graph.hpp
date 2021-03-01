#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <array>

#include "ILGen.hpp"

namespace pl0compiler { namespace compiler {

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

        Trans(const Type type, const void *value, const unsigned int idxNext, const unsigned int idxAlter, const func funct);

        const Type m_type;
        const void *m_value;
        const unsigned int m_idxNext;
        const unsigned int m_idxAlter;
        const func m_funct;
    };

    static Trans *getEntrance();

private:
    static const std::array<Trans,4> s_program;
    static const std::array<Trans,21> s_block;
    static const std::array<Trans,26> s_statement;
    static const std::array<Trans,11> s_condition;
    static const std::array<Trans,8> s_expression;
    static const std::array<Trans,7> s_term;
    static const std::array<Trans,6> s_factor;
};

} }
