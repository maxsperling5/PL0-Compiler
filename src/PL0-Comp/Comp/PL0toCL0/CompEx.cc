/************************/
/* Author: Max Sperling */
/************************/

#include "CompEx.hh"

using namespace std;

CompEx::CompEx(Token *token)
{
	this->token = token;
}

string CompEx::getError()
{
	string strErr = "Error: Value -> " + token->getVal()
                    + ", Row -> " + to_string(token->getRow())
                    + ", Col -> " + to_string(token->getCol())
                    + "\n";
    return strErr;
}
