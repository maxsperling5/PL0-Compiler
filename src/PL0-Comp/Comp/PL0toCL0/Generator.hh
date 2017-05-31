#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <deque>
class ILGen;
class Trans;
class Graph;
#include "Token.hh"

class Generator
{
public:
    Generator();
    ~Generator();

    void exec(std::deque<Token> &token, std::deque<char> &binary);

private:
    void generate(Trans *curSect);
    void execFunc(Trans *curTrans);

    Graph *graph;
    ILGen *ilgen;
    std::deque<Token> *token;
};
