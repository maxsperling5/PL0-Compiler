#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include "Token.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

class CompEx : public std::exception
{
private:
    Token *m_token;

public:
    CompEx(Token *token);
    std::string getError();
};

} } }
