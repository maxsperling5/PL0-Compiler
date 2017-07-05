/************************/
/* Author: Max Sperling */
/************************/

#include "CompEx.hh"

using namespace std;

CompEx::CompEx(Token *token)
{
    m_token = token;
}

string CompEx::getError()
{
    string strErr = "Error: Value -> " + m_token->getVal()
                    + ", Row -> " + to_string(m_token->getRow())
                    + ", Col -> " + to_string(m_token->getCol())
                    + "\n";
    return strErr;
}
