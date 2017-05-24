#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Trans.hh"

class Graph
{
public:
    Graph();

    Trans program[4];
    Trans block[21];
    Trans statement[26];
    Trans condition[11];
    Trans expression[8];
    Trans term[7];
    Trans factor[6];
};
