#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <deque>
class ILGen;
#include "Graph.hpp"
#include "Token.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

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
