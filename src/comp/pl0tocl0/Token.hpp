#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

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
    std::string m_val;
    TokenTyp m_typ;
    unsigned int m_row;
    unsigned int m_col;
};

} } }
