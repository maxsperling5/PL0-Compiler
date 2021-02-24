/************************/
/* Author: Max Sperling */
/************************/

#include "DataFactory.hpp"
#include "file/DataFile.hpp"

using namespace std;

pl0compiler::data::IDataPtr
pl0compiler::data::DataFactory::create(DataType type)
{
    IDataPtr dataPtr;
    switch(type)
    {
    case DataType::File:
        dataPtr = make_shared<file::DataFile>();
        break;
    }
    return dataPtr;
}
