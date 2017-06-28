#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <array>
#include <deque>
#include "Token.hh"

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

    std::array<int,8*16> classVec;
    std::array<std::array<int,10>,12> stateMat;
    std::array<std::array<func,10>,12> functMat;
	std::array<std::string,14> keywords;

    std::string srcCode;
    std::deque<Token> *token;
    Token curToken;

	unsigned int srcPos;
	unsigned int srcRow;
	unsigned int srcCol;
    unsigned int fsmState;
};
