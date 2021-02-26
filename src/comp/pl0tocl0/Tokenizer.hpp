#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

#include <vector>
#include <string>
#include <deque>

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

class Tokenizer
{
public:
    Tokenizer();

    /**
     * @param[in]  srcCode ... source code
     * @param[out] token   ... token list
     */
    void exec(std::string &srcCode, std::deque<Token> &token);

private:
    typedef void (Tokenizer::*func)();

    static const std::vector<int> s_classVec;
    static const std::vector<std::vector<int>> s_stateMat;
    static const std::vector<std::vector<func>> s_functMat;
    static const std::vector<std::string> s_keywords;

    void tokenize();
    void r();
    void wr();
    void gr();
    void wrc();
    void c();

    std::string *m_srcCode;
    std::deque<Token> *m_token;
    Token m_curToken;

    unsigned int m_srcPos;
    unsigned int m_srcRow;
    unsigned int m_srcCol;
    unsigned int m_fsmState;
};

} } }
