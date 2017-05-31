#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <vector>
#include "Token.hh"

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer(){}

    bool exec(std::string srcCode, std::vector<Token> &token);

private:
    typedef void (Tokenizer::*func)();

    bool tokenize();
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
    std::vector<Token> *token;
    Token curToken;
    unsigned int fsmState;

	unsigned int srcPos;
	unsigned int srcRow;
	unsigned int srcCol;
};
