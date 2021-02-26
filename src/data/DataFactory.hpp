#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IData.hpp"

namespace pl0compiler { namespace data {

enum DataType
{
    File
};

class DataFactory
{
public:
    static IDataUPtr create(DataType type);
};

} }
