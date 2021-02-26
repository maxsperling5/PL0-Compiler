/************************/
/* Author: Max Sperling */
/************************/

#include "CompEx.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

CompEx::CompEx(Token *token)
{
    m_token = token;
}

std::string CompEx::getError()
{
    std::string strErr = "Error: Value -> " + m_token->getVal()
                       + ", Row -> " + std::to_string(m_token->getRow())
                       + ", Col -> " + std::to_string(m_token->getCol())
                       + "\n";
    return strErr;
}

} } }
