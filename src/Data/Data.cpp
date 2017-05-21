/************************/
/* Author: Max Sperling */
/************************/

#ifndef DATA
#define DATA

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

class Data
{
private:
    string filePath;

public:
    Data(){}

    void setPath(string filePath)
    {
        this->filePath = filePath;
    }

    string readString()
    {
        ifstream t(filePath.c_str());
        stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

    void writeBinary(vector<char> bin)
    {
        string path = filePath + ".cl0";
        ofstream outfile(path, ios_base::binary);
        copy(bin.begin(), bin.end(), ostreambuf_iterator<char>(outfile));
        outfile.close();
    }
};

#endif
