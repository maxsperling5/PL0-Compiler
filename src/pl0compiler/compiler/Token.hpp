#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>

namespace pl0compiler { namespace compiler {

class Token
{
public:
    enum class Type
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
    void setTyp(Type typ);

    std::string getVal();
    Type getTyp();
    unsigned int getRow();
    unsigned int getCol();

private:
    std::string m_val;
    Type m_typ;
    unsigned int m_row;
    unsigned int m_col;
};

} }
