#ifndef LEXERPL0_H
#define LEXERPL0_H

#include "Lexer.h"

class LexerPL0 : public Lexer {
private:
	int *classVec[8*16];
	int *stateMat[12][10];
public:
	LexerPL0();
};

#endif