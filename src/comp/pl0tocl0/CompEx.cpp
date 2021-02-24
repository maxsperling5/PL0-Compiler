/************************/
/* Author: Max Sperling */
/************************/

#include "CompEx.hpp"

using namespace std;

pl0compiler::comp::pl0tocl0::CompEx::CompEx(Token *token)
{
    m_token = token;
}

string
pl0compiler::comp::pl0tocl0::CompEx::getError()
{
    string strErr = "Error: Value -> " + m_token->getVal()
                    + ", Row -> " + to_string(m_token->getRow())
                    + ", Col -> " + to_string(m_token->getCol())
                    + "\n";
    return strErr;
}
