#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <array>
#include <deque>
#include "Token.hpp"

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer(){}

    void exec(std::string srcCode, std::deque<Token> &token);

private:
    typedef void (Tokenizer::*func)();

    void tokenize();
    void r();
    void wr();
    void gr();
    void wrc();
    void c();

    std::array<int,8*16> m_classVec;
    std::array<std::array<int,10>,12> m_stateMat;
    std::array<std::array<func,10>,12> m_functMat;
    std::array<std::string,14> m_keywords;

    std::string m_srcCode;
    std::deque<Token> *m_token;
    Token m_curToken;

    unsigned int m_srcPos;
    unsigned int m_srcRow;
    unsigned int m_srcCol;
    unsigned int m_fsmState;
};
