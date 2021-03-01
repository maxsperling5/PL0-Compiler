#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Graph.hpp"
#include "Token.hpp"

#include <deque>

namespace pl0compiler { namespace compiler {

class ILGen;

class Generator
{
public:
    /**
     * @param[in]  token  ... token list
     * @param[out] binary ... binary list
     */
    void exec(std::deque<Token> &token, std::deque<char> &binary);

private:
    void generate(const Graph::Trans *curSect);
    void execFunc(const Graph::Trans *curTrans);

    ILGen m_ilgen;
    std::deque<Token> *m_token;
};

} }
