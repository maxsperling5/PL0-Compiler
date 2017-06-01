/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hh"

using namespace std;

void Token::init(int row, int col)
{
    this->row = row;
    this->col = col;
}

void Token::reset()
{
    val = "";
    typ = Undefined;
    row = 1;
    col = 1;
}

void Token::addChar(char c)
{
    val += c;
}

void Token::setTyp(TokenTyp typ)
{
    this->typ = typ;
}

string Token::getVal()
{
    return val;
}

Token::TokenTyp Token::getTyp()
{
    return typ;
}

unsigned int Token::getRow()
{
    return row;
}

unsigned int Token::getCol()
{
    return col;
}
