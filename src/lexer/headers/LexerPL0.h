#ifndef LEXERPL0_H
#define LEXERPL0_H

#include "Lexer.h"

typedef void (*func) (void);

class LexerPL0 : public Lexer {
private:
	string fstr;

	int srcPos;
	int srcRow;
	int srcCol;
	int fsmState;
	void initFSM();

	static const int classVec[8*16];
	static const int stateMat[12][10];
	static const func functMat[12][10];

	static void r();
	static void wr();
	static void gr();
	static void wrc();
	static void c();
public:
	LexerPL0();
	vector<Token> getToken(string fstr);
};

#endif