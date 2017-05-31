#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>

class Token
{
public:
    Token(){}

    enum TokenTyp
    {
        Undefined,
        Symbol,
        Number,
        Identifier,
        Keyword,
        String
    };

    void init(int row, int col);
    void reset();

    void addChar(char c);
    void setTyp(TokenTyp typ);

    std::string getVal();
    TokenTyp getTyp();
    unsigned int getRow();
    unsigned int getCol();

private:
    std::string val;
    TokenTyp typ;
    unsigned int row;
    unsigned int col;
};
