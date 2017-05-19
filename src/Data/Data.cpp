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
public:
    Data(){}

    string readString(string filePath)
    {
        ifstream t(filePath.c_str());
        stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

    void writeBinary(vector<unsigned char> bin)
    {
        string path = "./expl/sc.pl0.cl0";
        std::ofstream outfile(path, std::ios_base::binary);
        std::copy(bin.begin(), bin.end(), std::ostreambuf_iterator<char>(outfile));
        outfile.close();
    }
};

#endif
