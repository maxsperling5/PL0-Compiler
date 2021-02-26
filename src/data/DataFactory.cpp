/************************/
/* Author: Max Sperling */
/************************/

#include "DataFactory.hpp"
#include "file/DataFile.hpp"

using namespace std;

pl0compiler::data::IDataUPtr
pl0compiler::data::DataFactory::create(DataType type)
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
