#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IData.hh"

class DataFile : public IData
{
public:
    DataFile(){}
    ~DataFile(){}

    // --- IData -----------------------------
    virtual bool init(int argc, char *argv[]);
    virtual bool read(std::string &str);
    virtual bool write(std::vector<char> bin);
    // ---------------------------------------

private:
    std::string filePath;
};
