#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <string>
#include <vector>

class IData;
typedef std::shared_ptr<IData> IDataPtr;

class IData
{
public:
    static IDataPtr create();
    virtual ~IData(){}

    virtual bool init(int argc, char *argv[]) = 0;
    virtual bool read(std::string &str) = 0;
    virtual bool write(std::vector<char> bin) = 0;
};
