/************************/
/* Author: Max Sperling */
/************************/

#ifndef LEXER
#define LEXER

#include <string>
#include <vector>
#include "Token.cpp"
using namespace std;

class Lexer
{
private:
    typedef void (Lexer::*func) (void);

    int classVec[8*16];
	int stateMat[12][10];
	func functMat[12][10];
	string keywords[14];

public:
    Lexer() :
        classVec
        {
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
        },
        stateMat
        {
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
        },
        functMat
        {
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
        },
        keywords
        {
            "CALL","DO","WHILE","IF","THEN","ELSE","BEGIN","END",
            "ODD","PUT","GET","VAR","CONST","PROCEDURE"
        }
	{}

private:
    vector<Token> token;
    string srcCode = "";
	int srcPos = 0;
	int srcRow = 0;
	int srcCol = 0;
	int fsmState = 0;
	Token curToken;

public:
	vector<Token> genToken(string code)
    {
        srcCode = code;
        curToken.init(srcRow, srcCol);
        lex();

        return token;
    }

private:
    void lex()
    {
        while(srcPos < srcCode.length())
        {
            int cTyp = classVec[srcCode[srcPos]];
            (this->*functMat[fsmState][cTyp])();
            fsmState = stateMat[fsmState][cTyp];
        }
    }

    void r()
    {
        char c = srcCode[srcPos];
        if(c == '\n') { srcRow++; srcCol=0; }
        else srcCol++;
        srcPos++;
    }

    void wr() // write + read
    {
        curToken.addChar(srcCode[srcPos]);
        r();
    }

    void gr()
    {
        curToken.addChar(toupper(srcCode[srcPos]));
        r();
    }

    void wrc()
    {
        wr();
        c();
    }

    void c()
    {
        switch(fsmState)
        {
            // Number
            case 1:
                curToken.setTyp(Token::Number);
                break;
            // Keyword or Identifier
            case 2:
                curToken.setTyp(Token::Identifier);
                for(auto &keyword : keywords)
                {
                    if(curToken.getVal() == keyword) {
                        curToken.setTyp(Token::Keyword);
                        break;
                    }
                }
                break;
            // String
            case 9:
                curToken.setTyp(Token::String);
                break;
            // Symbol
            default:
                curToken.setTyp(Token::Symbol);
                break;
        }
        token.push_back(curToken);
        curToken.reset();
        curToken.init(srcRow, srcCol);
    }
};

#endif
