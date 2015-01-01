#include "../headers/LexerPL0.h"

LexerPL0::LexerPL0() {
	initFSM();
}

void LexerPL0::initFSM() {
	srcPos = 0;
	srcRow = 0;
	srcCol = 0;
	fsmState = 0;
}

const int LexerPL0::classVec[8*16] = {
	/*     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F     */
	/*--------------------------------------------------------*/
	/* 0*/ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/* 0*/
	/*10*/ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/*10*/
	/*20*/ 7, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*20*/
	/*30*/ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 5, 4, 6, 0,/*30*/
	/*40*/ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*40*/
	/*50*/ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 9, 0, 0, 0,/*50*/
	/*60*/ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*60*/
	/*70*/ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 /*70*/
};

const int LexerPL0::stateMat[12][10] = {
	/*     So  Zi  Bu  ':' '=' '<' '>' ' ' '"' '\'     */
	/*-------------------------------------------------*/
	/* 0*/ {0,  1,  2,  3,  0,  4,  5,  0,  9,  0},/* 0*/
	/* 1*/ {0,  1,  0,  0,  0,  0,  0,  0,  0,  0},/* 1*/
	/* 2*/ {0,  2,  2,  0,  0,  0,  0,  0,  0,  0},/* 2*/
	/* 3*/ {0,  0,  0,  0,  6,  0,  0,  0,  0,  0},/* 3*/
	/* 4*/ {0,  0,  0,  0,  7,  0,  0,  0,  0,  0},/* 4*/
	/* 5*/ {0,  0,  0,  0,  8,  0,  0,  0,  0,  0},/* 5*/
	/* 6*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},/* 6*/
	/* 7*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},/* 7*/
	/* 8*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},/* 8*/
	/* 9*/ {9,  9,  9,  9,  9,  9,  9,  9, 11, 10},/* 9*/
	/*10*/ {9,  9,  9,  9,  9,  9,  9,  9,  9,  9},/*10*/
	/*11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0} /*11*/
};

const func LexerPL0::functMat[12][10] = {
	/*      So   Zi    Bu   ':'  '='  '<'  '>'  ' '  ''  '\'      */
	/*------------------------------------------------------------*/
	/* 0*/ {wrc,  wr,  gr,  wr,  wrc,  wr,  wr,  r, wrc, wrc},/* 0*/
	/* 1*/ {  c,  wr,   c,   c,    c,   c,   c,  c,   c,   c},/* 1*/
	/* 2*/ {  c,  wr,  gr,   c,    c,   c,   c,  c,   c,   c},/* 2*/
	/* 3*/ {  c,   c,   c,   c,   wr,   c,   c,  c,   c,   c},/* 3*/
	/* 4*/ {  c,   c,   c,   c,   wr,   c,   c,  c,   c,   c},/* 4*/
	/* 5*/ {  c,   c,   c,   c,   wr,   c,   c,  c,   c,   c},/* 5*/
	/* 6*/ {  c,   c,   c,   c,    c,   c,   c,  c,   c,   c},/* 6*/
	/* 7*/ {  c,   c,   c,   c,    c,   c,   c,  c,   c,   c},/* 7*/
	/* 8*/ {  c,   c,   c,   c,    c,   c,   c,  c,   c,   c},/* 8*/
	/* 9*/ { wr,  wr,  wr,  wr,   wr,  wr,  wr, wr,   c,   r},/* 9*/
	/*10*/ { wr,  wr,  wr,  wr,   wr,  wr,  wr, wr,  wr,  wr},/*10*/
	/*11*/ {wrc, wrc, wrc, wrc,  wrc, wrc, wrc,wrc, wrc,  wrc}/*11*/
};

void LexerPL0::r() {
	char c = fstr[srcPos];

	if(c == '\n') { srcRow++; srcCol=0; }
	else srcCol++;
	srcPos++;

	int ctyp = classVec[c];
	fsmState = stateMat[fsmState][ctyp];
}

void LexerPL0::wr() {

	r();
}

void LexerPL0::gr() {

	r();
}

void LexerPL0::wrc() {
	wr();
	c();
}

void LexerPL0::c() {
	Token tok(tokRow, tokCol);

	token.push_back(tok);
}

vector<Token> LexerPL0::getToken(string fstr) {
	this->fstr = fstr;
	initFSM();

	while(srcPos < fstr.length()) {
		int tokRow = srcRow;
		int tokCol = srcCol;
		
		functMat[fsmState][fstr[srcPos]];
	}
}