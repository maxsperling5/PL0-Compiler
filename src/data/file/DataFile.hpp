#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "../IData.hpp"

namespace pl0compiler { namespace data { namespace file {

class DataFile : public IData
{
public:
    DataFile(){}
    ~DataFile(){}

    // --- IData -----------------------------
    virtual bool init(int argc, char *argv[]);
    virtual bool read(std::string &str);
    virtual bool write(std::deque<char> bin);
    // ---------------------------------------

private:
    std::string m_pl0File;
    std::string m_cl0File;
};

} } }