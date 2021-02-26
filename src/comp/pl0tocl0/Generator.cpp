/************************/
/* Author: Max Sperling */
/************************/

#include "Generator.hpp"

#include "ILGen.hpp"
#include "CompEx.hpp"

using namespace std;

pl0compiler::comp::pl0tocl0::Generator::Generator()
{
    m_ilgen = new ILGen();
}

pl0compiler::comp::pl0tocl0::Generator::~Generator()
{
    delete m_ilgen;
}

void
pl0compiler::comp::pl0tocl0::Generator::exec(deque<Token> &token, deque<char> &binary)
{
    m_token = &token;
    generate(Graph::getEntrance());
    binary = m_ilgen->getBinary();
}

void
pl0compiler::comp::pl0tocl0::Generator::generate(const Graph::Trans *curSect)
{
    bool IsFinished = false;
    const Graph::Trans *curTrans = curSect;

    while (!IsFinished)
    {
        switch (curTrans->m_type)
        {
        case Graph::Trans::Nil:
            execFunc(curTrans);
            curTrans = &curSect[curTrans->m_idxNext];
            break;
        case Graph::Trans::Symbol:
            if (string((char*)curTrans->m_value) == m_token->front().getVal())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) throw CompEx(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::Token:
            if (Token::TokenTyp(*(int*)curTrans->m_value) == m_token->front().getTyp())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) throw CompEx(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::GraphStart:
            try
            {
                generate((Graph::Trans*)curTrans->m_value);
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
            }
            catch (...)
            {
                if (curTrans->m_idxAlter == 0) throw CompEx(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::GraphEnd:
            execFunc(curTrans);
            IsFinished = true;
            break;
        }
    }
}

void
pl0compiler::comp::pl0tocl0::Generator::execFunc(const Graph::Trans *curTrans)
{
    if (curTrans->m_funct == nullptr) return;
    (m_ilgen->*curTrans->m_funct)((void*)&(m_token->front()));
}
