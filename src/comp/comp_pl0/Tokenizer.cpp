/************************/
/* Author: Max Sperling */
/************************/

#include "Tokenizer.hpp"

using namespace std;

Tokenizer::Tokenizer()
{
    m_classVec =
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
    };

    m_stateMat =
    {{
    /*      So  Zi  Bu  ':' '=' '<' '>' ' ' '"' '\'      */
    /*---------------------------------------------------*/
    /* 0*/ {{0,  1,  2,  3,  0,  4,  5,  0,  9,  0}},/* 0*/
    /* 1*/ {{0,  1,  0,  0,  0,  0,  0,  0,  0,  0}},/* 1*/
    /* 2*/ {{0,  2,  2,  0,  0,  0,  0,  0,  0,  0}},/* 2*/
    /* 3*/ {{0,  0,  0,  0,  6,  0,  0,  0,  0,  0}},/* 3*/
    /* 4*/ {{0,  0,  0,  0,  7,  0,  0,  0,  0,  0}},/* 4*/
    /* 5*/ {{0,  0,  0,  0,  8,  0,  0,  0,  0,  0}},/* 5*/
    /* 6*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 6*/
    /* 7*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 7*/
    /* 8*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 8*/
    /* 9*/ {{9,  9,  9,  9,  9,  9,  9,  9, 11, 10}},/* 9*/
    /*10*/ {{9,  9,  9,  9,  9,  9,  9,  9,  9,  9}},/*10*/
    /*11*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}} /*11*/
    }};

    m_functMat =
    {{
    /*       So   Zi    Bu   ':'  '='  '<'  '>'   ' '  ''  '\'       */
    /*---------------------------------------------------------------*/
    /* 0*/ {{&Tokenizer::wrc,  &Tokenizer::wr,  &Tokenizer::gr,  &Tokenizer::wr,  &Tokenizer::wrc,  &Tokenizer::wr,  &Tokenizer::wr,   &Tokenizer::r, &Tokenizer::wrc, &Tokenizer::wrc}},/* 0*/
    /* 1*/ {{&Tokenizer::c,  &Tokenizer::wr,   &Tokenizer::c,   &Tokenizer::c,    &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 1*/
    /* 2*/ {{&Tokenizer::c,  &Tokenizer::wr,  &Tokenizer::gr,   &Tokenizer::c,    &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 2*/
    /* 3*/ {{&Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::wr,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 3*/
    /* 4*/ {{&Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::wr,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 4*/
    /* 5*/ {{&Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::wr,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 5*/
    /* 6*/ {{&Tokenizer::c,  &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,    &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 6*/
    /* 7*/ {{&Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,    &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 7*/
    /* 8*/ {{&Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,    &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c,   &Tokenizer::c}},/* 8*/
    /* 9*/ {{&Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,   &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,   &Tokenizer::c,   &Tokenizer::r}},/* 9*/
    /*10*/ {{&Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,   &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr,  &Tokenizer::wr}},/*10*/
    /*11*/ {{&Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc,  &Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc, &Tokenizer::wrc}} /*11*/
    }};

    m_keywords =
    {
        "CALL","DO","WHILE","IF","THEN","ELSE","BEGIN","END",
        "ODD","PUT","GET","VAR","CONST","PROCEDURE"
    };

    m_srcPos = 0;
    m_srcRow = 1;
    m_srcCol = 1;
    m_fsmState = 0;
}

void Tokenizer::exec(string srcCode, deque<Token> &token)
{
    m_srcCode = srcCode;
    m_token = &token;
    m_curToken.init(m_srcRow, m_srcCol);
    tokenize();
}

void Tokenizer::tokenize()
{
    while(m_srcPos < m_srcCode.length())
    {
        int cTyp = m_classVec.at((int)m_srcCode.at(m_srcPos));
        (this->*m_functMat.at(m_fsmState).at(cTyp))();
        m_fsmState = m_stateMat.at(m_fsmState).at(cTyp);
    }
}

void Tokenizer::r()
{
    char c = m_srcCode.at(m_srcPos);
    if(c == '\n') { m_srcRow++; m_srcCol=1; }
    else m_srcCol++;
    m_srcPos++;
}

void Tokenizer::wr()
{
    m_curToken.addChar(m_srcCode.at(m_srcPos));
    r();
}

void Tokenizer::gr()
{
    m_curToken.addChar(toupper(m_srcCode.at(m_srcPos)));
    r();
}

void Tokenizer::wrc()
{
    wr();
    c();
}

void Tokenizer::c()
{
    switch(m_fsmState)
    {
        // Number
        case 1:
            m_curToken.setTyp(Token::Number);
            break;
        // Keyword or Identifier
        case 2:
            m_curToken.setTyp(Token::Identifier);
            for(auto &keyword : m_keywords)
            {
                if(m_curToken.getVal() == keyword) {
                    m_curToken.setTyp(Token::Keyword);
                    break;
                }
            }
            break;
        // String
        case 9:
            m_curToken.setTyp(Token::String);
            break;
        // Symbol
        default:
            m_curToken.setTyp(Token::Symbol);
            break;
    }
    m_token->push_back(m_curToken);
    m_curToken.reset();
    m_curToken.init(m_srcRow, m_srcCol);
}

