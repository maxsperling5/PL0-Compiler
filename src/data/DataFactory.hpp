#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IData.hpp"

enum DataType
{
    File
};

class DataFactory
{
public:
    static IDataPtr create(DataType type);
};