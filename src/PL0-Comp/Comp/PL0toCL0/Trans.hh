#pragma once
/************************/
/* Author: Max Sperling */
/************************/

class ILGen;

using namespace std;

class Trans
{
public:
    Trans(){}
    ~Trans(){}

    enum TransTyp
    {
        Nil,
        Symbol,
        Token,
        GraphStart,
        GraphEnd
    };

    typedef void (ILGen::*func)(void*);

    Trans(TransTyp typ, const void *value, int idxNext, int idxAlter, func funct);

    TransTyp typ;
    const void *value;
    int idxNext;
    int idxAlter;
    func funct;
};
