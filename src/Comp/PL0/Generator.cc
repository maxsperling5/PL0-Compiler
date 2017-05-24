/************************/
/* Author: Max Sperling */
/************************/

#include "Generator.hh"

#include "ILGen.hh"
#include "Graph.hh"
#include "Trans.hh"

using namespace std;

Generator::Generator()
{
    graph = new Graph();
    ilgen = new ILGen();
}

Generator::~Generator()
{
    delete ilgen;
    delete graph;
}

std::vector<char> Generator::exec(std::vector<Token> token)
{
    this->token = token;
    posTok = 0;
    generate(&graph->program[0]);
    return ilgen->getBinary();
}

bool Generator::generate(Trans *curSect)
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
            if(string((char*)curTrans->value) == token[posTok].getVal())
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
            if(Token::TokenTyp((int)curTrans->value) == token[posTok].getTyp())
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
            if(generate((Trans*)curTrans->value))
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

bool Generator::execFunc(Trans *curTrans)
{
    if(curTrans->funct == nullptr)
        return false;
    else
        (ilgen->*curTrans->funct)((void*)&token[posTok]);
    return true;
}
