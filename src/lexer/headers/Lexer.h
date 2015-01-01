#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>
using namespace std;

class Lexer {
protected:
	vector<Token> token;
public:
	virtual vector<Token> getToken(string fstr) = 0;
};

#endif