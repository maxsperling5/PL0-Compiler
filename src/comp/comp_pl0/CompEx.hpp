#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include "Token.hpp"

class CompEx : public std::exception
{
private:
    Token *m_token;

public:
    CompEx(Token *token);
    std::string getError();
};
