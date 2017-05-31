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
    if(argc != 2) return false;
    this->filePath = argv[1];
    return true;
}

bool DataFile::read(string &str)
{
    ifstream ifs(filePath);
    if(ifs.fail()) return false;
    str = {istreambuf_iterator<char>(ifs), istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool DataFile::write(std::deque<char> bin)
{
    ofstream ofs(filePath + ".cl0", ios_base::binary);
    if(ofs.fail()) return false;
    copy(bin.begin(), bin.end(), ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}
