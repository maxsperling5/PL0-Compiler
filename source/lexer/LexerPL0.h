#ifndef LEXERPL0_H
#define LEXERPL0_H

#include "Lexer.h"

class LexerPL0 : public Lexer {
private:
	typedef void (LexerPL0::*func) (void);

	vector<Token> vecToken;
	string strSourcecode;

	int srcPos;
	int srcRow;
	int srcCol;
	int fsmState;

	int classVec[8*16];
	int stateMat[12][10];
	func functMat[12][10];

	void initFSM();

	void r();
	void wr();
	void gr();
	void wrc();
	void c();
public:
	LexerPL0();
	vector<Token> getTokenVec(string strSourcecode);
};

#endif