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
        enum Typ
        {
            Nil, Symbol, Token, GraphStart, GraphEnd
        };

        Trans(){}
        Trans(Typ typ, const void *value, int idxNext, int idxAlter, func funct);

        Typ typ;
        const void *value;
        unsigned int idxNext;
        unsigned int idxAlter;
        func funct;
    };

public:
    Graph();

    std::array<Trans,4> program;
    std::array<Trans,21> block;
    std::array<Trans,26> statement;
    std::array<Trans,11> condition;
    std::array<Trans,8> expression;
    std::array<Trans,7> term;
    std::array<Trans,6> factor;
};
