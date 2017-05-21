/************************/
/* Author: Max Sperling */
/************************/

#ifndef PARSER
#define PARSER

#include "./Graph.cpp"
#include "./Trans.cpp"
#include "../Lexer/Token.cpp"
#include <cstdint>
#include <vector>
#include <iostream>
using namespace std;

class Parser
{
private:
    vector<Token> tok;
    Graph *gra;
    Generator *gen;

public:
    Parser(vector<Token> token)
    {
        tok = token;
        gra = new Graph();
        gen = new Generator();
    }

private:
    int posTok;

public:
    vector<char> genBinary(vector<Token> tok)
    {
        posTok = 0;
        parse(&gra->program[0]);
        return gen->getBinary();
    }

    bool parse(Trans *curSect)
    {
        bool IsFinished = false;
        Trans *curTrans = &curSect[0];

        while(!IsFinished)
        {
            switch(curTrans->typ)
            {
            case Trans::Nil:
                execFunc(curTrans);
                curTrans = &curSect[curTrans->idxNext];
                break;
            case Trans::Symbol:
                if(string((char*)curTrans->value) == tok[posTok].getVal())
                {
                    execFunc(curTrans);
                    curTrans = &curSect[curTrans->idxNext];
                    posTok++;
                }
                else
                {
                    if(curTrans->idxAlter == 0) return false;
                    curTrans = &curSect[curTrans->idxAlter];
                }
                break;
            case Trans::Token:
                if(Token::TokenTyp((int)curTrans->value) == tok[posTok].getTyp())
                {
                    execFunc(curTrans);
                    curTrans = &curSect[curTrans->idxNext];
                    posTok++;
                }
                else
                {
                    if(curTrans->idxAlter == 0) return false;
                    curTrans = &curSect[curTrans->idxAlter];
                }
                break;
            case Trans::GraphStart:
                if(parse((Trans*)curTrans->value))
                {
                    execFunc(curTrans);
                    curTrans = &curSect[curTrans->idxNext];
                }
                else
                {
                    if(curTrans->idxAlter == 0) return false;
                    curTrans = &curSect[curTrans->idxAlter];
                }
                break;
            case Trans::GraphEnd:
                execFunc(curTrans);
                IsFinished = true;
                break;
            }
        }
        return true;
    }

private:
    bool execFunc(Trans *curTrans)
    {
        if(curTrans->funct == nullptr)
            return false;
        else
            (gen->*curTrans->funct)((void*)&tok[posTok]);
        return true;
    }

public:
    ~Parser()
    {
        delete gra;
    }
};

#endif
