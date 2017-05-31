#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>

#include "Token.hh"

class CompExcp : public std::exception
{
private:
    Token *token;

public:
    CompExcp(Token *token);
    std::string getError();
};
