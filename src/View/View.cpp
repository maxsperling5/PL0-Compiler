/************************/
/* Author: Max Sperling */
/************************/

#ifndef VIEW
#define VIEW

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "../Lexer/Token.cpp"
using namespace std;

class View
{
public:
    View(){}

    void writeString(string str)
    {
        cout << "Write string:" << endl;
        cout << str;
    }

    void writeToken(vector<Token> tok)
    {
        cout << "Write token:" << endl;
        for(auto &t : tok)
        {
            cout << t.getVal() << endl;
        }
    }

    void writeBinary(vector<unsigned char> bin)
    {
        cout << "Write binary:" << endl;
        for(auto &b : bin)
        {
            cout << setfill('0') << setw(2) << hex << +b;
        }
    }
};

#endif
