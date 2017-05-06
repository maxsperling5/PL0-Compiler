#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>
using namespace std;

class Lexer {
public:
	virtual vector<Token> getTokenVec(string strSourcecode) = 0;
};

#endif