/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

using namespace std;

void
pl0compiler::comp::pl0tocl0::Token::init(int row, int col)
{
    m_row = row;
    m_col = col;
}

void
pl0compiler::comp::pl0tocl0::Token::reset()
{
    m_val = "";
    m_typ = Undefined;
    m_row = 1;
    m_col = 1;
}

void
pl0compiler::comp::pl0tocl0::Token::addChar(char c)
{
    m_val += c;
}

void
pl0compiler::comp::pl0tocl0::Token::setTyp(TokenTyp typ)
{
    m_typ = typ;
}

string
pl0compiler::comp::pl0tocl0::Token::getVal()
{
    return m_val;
}

pl0compiler::comp::pl0tocl0::Token::TokenTyp
pl0compiler::comp::pl0tocl0::Token::getTyp()
{
    return m_typ;
}

unsigned int
pl0compiler::comp::pl0tocl0::Token::getRow()
{
    return m_row;
}

unsigned int
pl0compiler::comp::pl0tocl0::Token::getCol()
{
    return m_col;
}
