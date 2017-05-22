/************************/
/* Author: Max Sperling */
/************************/

#ifndef TRANS
#define TRANS

#include "GeneratorPL0.cpp"
#include <functional>
using namespace std;

class Trans
{
public:
    enum TransTyp
    {
        Nil,
        Symbol,
        Token,
        GraphStart,
        GraphEnd
    };

public:
    typedef void (Generator::*func)(void*);

    TransTyp typ;
    const void *value;
    int idxNext;
    int idxAlter;
    func funct;

    Trans(TransTyp typ, const void *value, int idxNext, int idxAlter, func funct)
    {
        this->typ = typ;
        this->value = value;
        this->idxNext = idxNext;
        this->idxAlter = idxAlter;
        this->funct = funct;
    }
};

#endif
