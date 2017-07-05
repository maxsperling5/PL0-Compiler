/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hh"

using namespace std;

void Token::init(int row, int col)
{
    m_row = row;
    m_col = col;
}

void Token::reset()
{
    m_val = "";
    m_typ = Undefined;
    m_row = 1;
    m_col = 1;
}

void Token::addChar(char c)
{
    m_val += c;
}

void Token::setTyp(TokenTyp typ)
{
    m_typ = typ;
}

string Token::getVal()
{
    return m_val;
}

Token::TokenTyp Token::getTyp()
{
    return m_typ;
}

unsigned int Token::getRow()
{
    return m_row;
}

unsigned int Token::getCol()
{
    return m_col;
}
