/************************/
/* Author: Max Sperling */
/************************/

#include "DataFile.hh"

#include <fstream>

using namespace std;

IDataPtr IData::create()
{
    return IDataPtr(new DataFile());
}

bool DataFile::init(int argc, char *argv[])
{
    if(argc != 3) return false;
    this->pl0File = argv[1];
    this->cl0File = argv[2];
    return true;
}

bool DataFile::read(string &str)
{
    ifstream ifs(pl0File);
    if(ifs.fail()) return false;
    str = {istreambuf_iterator<char>(ifs), istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool DataFile::write(std::deque<char> bin)
{
    ofstream ofs(cl0File, ios_base::binary);
    if(ofs.fail()) return false;
    copy(bin.begin(), bin.end(), ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}
