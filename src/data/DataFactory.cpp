/************************/
/* Author: Max Sperling */
/************************/

#include "DataFactory.hpp"
#include "data_file/DataFile.hpp"

using namespace std;

IDataPtr DataFactory::create(DataType type)
{
    IDataPtr dataPtr;
    switch(type)
    {
    case DataType::File:
        dataPtr = make_shared<DataFile>();
        break;
    }
    return dataPtr;
}