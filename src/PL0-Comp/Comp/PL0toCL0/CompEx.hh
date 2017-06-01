#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include "Token.hh"

class CompEx : public std::exception
{
private:
    Token *token;

public:
    CompEx(Token *token);
    std::string getError();
};
