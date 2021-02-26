#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Graph.hpp"
#include "Token.hpp"

#include <deque>

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

class ILGen;

class Generator
{
public:
    Generator();
    ~Generator();

    void exec(std::deque<Token> &token, std::deque<char> &binary);

private:
    void generate(Graph::Trans *curSect);
    void execFunc(Graph::Trans *curTrans);

    Graph *m_graph;
    ILGen *m_ilgen;
    std::deque<Token> *m_token;
};

} } }
