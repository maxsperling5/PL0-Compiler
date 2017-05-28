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

    bool exec(std::vector<Token> &token, std::vector<char> &binary);

private:
    bool generate(Trans *curSect);
    bool execFunc(Trans *curTrans);

    Graph *graph;
    ILGen *ilgen;
    std::vector<Token> *token;
    unsigned int posTok;
};
