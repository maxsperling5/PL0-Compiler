/************************/
/* Author: Max Sperling */
/************************/

#include "FileIO.hpp"

#include <fstream>

namespace pl0compiler { namespace fileio {

bool FileIO::init(int argc, char *argv[])
{
    if (argc != 3) return false;
    m_pl0File = argv[1];
    m_cl0File = argv[2];
    return true;
}

bool FileIO::read(std::string &str)
{
    std::ifstream ifs(m_pl0File);
    if (ifs.fail()) return false;
    str = {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool FileIO::write(std::deque<char> bin)
{
    std::ofstream ofs(m_cl0File, std::ios_base::binary);
    if (ofs.fail()) return false;
    copy(bin.begin(), bin.end(), std::ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}

} }
