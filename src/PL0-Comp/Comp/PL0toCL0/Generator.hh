#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <deque>
class ILGen;
#include "Graph.hh"
#include "Token.hh"

class Generator
{
public:
    Generator();
    ~Generator();

    void exec(std::deque<Token> &token, std::deque<char> &binary);

private:
    void generate(Graph::Trans *curSect);
    void execFunc(Graph::Trans *curTrans);

    Graph *graph;
    ILGen *ilgen;
    std::deque<Token> *token;
};
