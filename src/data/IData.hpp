#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <string>
#include <deque>

namespace pl0compiler { namespace data {

class IData;
typedef std::unique_ptr<IData> IDataUPtr;

class IData
{
public:
    virtual ~IData(){}

    virtual bool init(int argc, char *argv[]) = 0;
    virtual bool read(std::string &str) = 0;
    virtual bool write(std::deque<char> bin) = 0;
};

} }
