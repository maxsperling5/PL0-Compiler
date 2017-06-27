/************************/
/* Author: Max Sperling */
/************************/

#include "Generator.hh"
#include "ILGen.hh"
#include "CompEx.hh"

using namespace std;

Generator::Generator()
{
    graph = new Graph();
    ilgen = new ILGen();
}

Generator::~Generator()
{
    delete graph;
    delete ilgen;
}

void Generator::exec(deque<Token> &token, deque<char> &binary)
{
    this->token = &token;
    generate(&graph->program.at(0));
    binary = ilgen->getBinary();
}

void Generator::generate(Graph::Trans *curSect)
{
    bool IsFinished = false;
    Graph::Trans *curTrans = curSect;

    while(!IsFinished)
    {
        switch(curTrans->typ)
        {
        case Graph::Trans::Nil:
            execFunc(curTrans);
            curTrans = &curSect[curTrans->idxNext];
            break;
        case Graph::Trans::Symbol:
            if(string((char*)curTrans->value) == token->front().getVal())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->idxNext];
                token->pop_front();
            }
            else
            {
                if(curTrans->idxAlter == 0) throw CompEx(&token->front());
                curTrans = &curSect[curTrans->idxAlter];
            }
            break;
        case Graph::Trans::Token:
            if(Token::TokenTyp((int)curTrans->value) == token->front().getTyp())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->idxNext];
                token->pop_front();
            }
            else
            {
                if(curTrans->idxAlter == 0) throw CompEx(&token->front());
                curTrans = &curSect[curTrans->idxAlter];
            }
            break;
        case Graph::Trans::GraphStart:
            try{
                generate((Graph::Trans*)curTrans->value);
                execFunc(curTrans);
                curTrans = &curSect[curTrans->idxNext];
            }catch(...)
            {
                if(curTrans->idxAlter == 0) throw CompEx(&token->front());
                curTrans = &curSect[curTrans->idxAlter];
            }
            break;
        case Graph::Trans::GraphEnd:
            execFunc(curTrans);
            IsFinished = true;
            break;
        }
    }
}

void Generator::execFunc(Graph::Trans *curTrans)
{
    if(curTrans->funct == nullptr) return;
    (ilgen->*curTrans->funct)((void*)&(token->front()));
}
