/************************/
/* Author: Max Sperling */
/************************/

#include "Tokenizer.hh"

using namespace std;

Tokenizer::Tokenizer() :
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
{
    string srcCode = "";
    srcPos = 0;
    srcRow = 0;
    srcCol = 0;
    fsmState = 0;
}

vector<Token> Tokenizer::exec(string srcCode)
{
    this->srcCode = srcCode;
    curToken.init(srcRow, srcCol);
    lex();
    return tok;
}

void Tokenizer::lex()
{
    while(srcPos < srcCode.length())
    {
        int cTyp = classVec[srcCode[srcPos]];
        (this->*functMat[fsmState][cTyp])();
        fsmState = stateMat[fsmState][cTyp];
    }
}

void Tokenizer::r()
{
    char c = srcCode[srcPos];
    if(c == '\n') { srcRow++; srcCol=0; }
    else srcCol++;
    srcPos++;
}

void Tokenizer::wr()
{
    curToken.addChar(srcCode[srcPos]);
    r();
}

void Tokenizer::gr()
{
    curToken.addChar(toupper(srcCode[srcPos]));
    r();
}

void Tokenizer::wrc()
{
    wr();
    c();
}

void Tokenizer::c()
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
    tok.push_back(curToken);
    curToken.reset();
    curToken.init(srcRow, srcCol);
}

