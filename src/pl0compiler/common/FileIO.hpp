#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <deque>

namespace pl0compiler { namespace common {

class FileIO
{
public:
    bool init(int argc, char *argv[]);
    bool read(std::string &str);
    bool write(std::deque<char> bin);

private:
    std::string m_pl0File;
    std::string m_cl0File;
};

} }