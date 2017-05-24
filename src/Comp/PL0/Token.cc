/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hh"

#include <string>

using namespace std;

void Token::init(int srcRow, int srcCol)
{
    this->srcRow = srcRow;
    this->srcCol = srcCol;
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

void Token::reset()
{
    val = "";
    typ = Undefined;
    srcRow = 0;
    srcCol = 0;
}
