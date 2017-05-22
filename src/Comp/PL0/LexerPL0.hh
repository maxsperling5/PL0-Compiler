#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <vector>

#include "Token.cpp"

class LexerPL0
{
public:
    LexerPL0();
    ~LexerPL0(){}

private:
    typedef void (LexerPL0::*func) (void);

    int classVec[8*16];
	int stateMat[12][10];
	func functMat[12][10];
	std::string keywords[14];

private:
    std::vector<Token> token;
    std::string srcCode = "";
	int srcPos = 0;
	int srcRow = 0;
	int srcCol = 0;
	int fsmState = 0;
	Token curToken;

	private:
    void lex()
    {
        while(srcPos < srcCode.length())
        {
            int cTyp = classVec[srcCode[srcPos]];
            (this->*functMat[fsmState][cTyp])();
            fsmState = stateMat[fsmState][cTyp];
        }
    }

    void r()
    {
        char c = srcCode[srcPos];
        if(c == '\n') { srcRow++; srcCol=0; }
        else srcCol++;
        srcPos++;
    }

    void wr() // write + read
    {
        curToken.addChar(srcCode[srcPos]);
        r();
    }

    void gr()
    {
        curToken.addChar(toupper(srcCode[srcPos]));
        r();
    }

    void wrc()
    {
        wr();
        c();
    }

    void c()
    {
        switch(fsmState)
        {
            // Number
            case 1:
                curToken.setTyp(Token::Number);
                break;
            // Keyword or Identifier
            case 2:
                curToken.setTyp(Token::Identifier);
                for(auto &keyword : keywords)
                {
                    if(curToken.getVal() == keyword) {
                        curToken.setTyp(Token::Keyword);
                        break;
                    }
                }
                break;
            // String
            case 9:
                curToken.setTyp(Token::String);
                break;
            // Symbol
            default:
                curToken.setTyp(Token::Symbol);
                break;
        }
        token.push_back(curToken);
        curToken.reset();
        curToken.init(srcRow, srcCol);
    }

public:
    vector<Token> genToken(string code);
};
