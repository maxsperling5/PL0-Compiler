#ifndef FREAD_H
#define FREAD_H

#include <string>
using namespace std;

class FRead {
protected:
public:
	virtual void open(string fpath) = 0;
	virtual bool isOpen() = 0;
	virtual string getStr() = 0;
};

#endif