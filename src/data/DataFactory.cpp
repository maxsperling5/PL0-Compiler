/************************/
/* Author: Max Sperling */
/************************/

#include "DataFactory.hpp"
#include "file/DataFile.hpp"

namespace pl0compiler { namespace data {

IDataUPtr DataFactory::create(DataType type)
{
    IDataUPtr dataUPtr;
    switch(type)
    {
    case DataType::File:
        dataUPtr.reset(new file::DataFile());
        break;
    }
    return dataUPtr;
}

} }
