﻿/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

namespace pl0compiler { namespace compiler {

void Token::init(int row, int col)
{
    m_row = row;
    m_col = col;
}

void Token::reset()
{
    m_val = "";
    m_typ = Type::Undefined;
    m_row = 1;
    m_col = 1;
}

void Token::addChar(char c)
{
    m_val += c;
}

void Token::setTyp(Token::Type typ)
{
    m_typ = typ;
}

std::string Token::getVal()
{
    return m_val;
}

Token::Type Token::getTyp()
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

} }
