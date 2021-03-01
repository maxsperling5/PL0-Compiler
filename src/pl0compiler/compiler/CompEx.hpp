#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

#include <string>

namespace pl0compiler { namespace compiler {

class CompEx : public std::exception
{
public:
    CompEx(Token *token);
    std::string getError();

private:
    Token *m_token;
};

} }
