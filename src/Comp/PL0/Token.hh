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

    void init(int srcRow, int srcCol);
    void addChar(char c);
    void setTyp(TokenTyp typ);
    std::string getVal();
    TokenTyp getTyp();
    void reset();

private:
    std::string val;
	TokenTyp typ;
	int srcRow;
	int srcCol;
};
