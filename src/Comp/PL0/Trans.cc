/************************/
/* Author: Max Sperling */
/************************/

#include "Trans.hh"

using namespace std;

Trans::Trans(TransTyp typ, const void *value, int idxNext, int idxAlter, func funct)
{
    this->typ = typ;
    this->value = value;
    this->idxNext = idxNext;
    this->idxAlter = idxAlter;
    this->funct = funct;
}
