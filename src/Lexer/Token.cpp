/************************/
/* Author: Max Sperling */
/************************/

#ifndef TOKEN
#define TOKEN

#include <string>
using namespace std;

class Token
{
public:
    enum TokenTyp
    {
        Undefined,
        Symbol,
        Number,
        Identifier,
        Keyword,
        String
    };

private:
    string val;
	TokenTyp typ;
	int srcRow;
	int srcCol;

public:
    Token(){}

    void init(int srcRow, int srcCol)
    {
        this->srcRow = srcRow;
        this->srcCol = srcCol;
    }

    void addChar(char c)
    {
        val += c;
    }

    void setTyp(TokenTyp typ)
    {
        this->typ = typ;
    }

    string getVal()
    {
        return val;
    }

    TokenTyp getTyp()
    {
        return typ;
    }

    void reset()
    {
        val = "";
        typ = Undefined;
        srcRow = 0;
        srcCol = 0;
    }
};

#endif
