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

    std::vector<Token> exec(std::string srcCode);

private:
    void lex();
    void r();
    void wr();
    void gr();
    void wrc();
    void c();

    typedef void (Tokenizer::*func) (void);
    int classVec[8*16];
	int stateMat[12][10];
	func functMat[12][10];
	std::string keywords[14];

    std::vector<Token> tok;
    std::string srcCode;
	int srcPos;
	int srcRow;
	int srcCol;
	int fsmState;
	Token curToken;
};
