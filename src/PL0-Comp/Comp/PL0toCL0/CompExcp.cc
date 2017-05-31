/************************/
/* Author: Max Sperling */
/************************/

#include "CompExcp.hh"

using namespace std;

CompExcp::CompExcp(Token *token)
{
	this->token = token;
}

string CompExcp::getError()
{
	string strErr = "Error: Value -> " + token->getVal()
                    + ", Row -> " + to_string(token->getRow())
                    + ", Col -> " + to_string(token->getCol())
                    + "\n";
    return strErr;
}
