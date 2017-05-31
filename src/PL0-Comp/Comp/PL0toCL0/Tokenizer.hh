#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
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

    int classVec[8*16];
	int stateMat[12][10];
	func functMat[12][10];
	std::string keywords[14];

    std::string srcCode;
    std::deque<Token> *token;
    Token curToken;
    unsigned int fsmState;

	unsigned int srcPos;
	unsigned int srcRow;
	unsigned int srcCol;
};
