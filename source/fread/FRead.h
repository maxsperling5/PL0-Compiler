#ifndef FREAD_H
#define FREAD_H

#include <string>
using namespace std;

class FRead {
public:
	virtual void open(string fpath) = 0;
	virtual bool isOpen() = 0;
	virtual string getText() = 0;
};

#endif