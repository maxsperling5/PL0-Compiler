#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <vector>
class ILGen;
class Trans;
class Graph;
#include "Token.hh"

class Generator
{
public:
    Generator();
    ~Generator();

    std::vector<char> exec(std::vector<Token> token);

private:
    bool generate(Trans *curSect);
    bool execFunc(Trans *curTrans);

    std::vector<Token> token;
    Graph *graph;
    ILGen *ilgen;
    int posTok;
};
