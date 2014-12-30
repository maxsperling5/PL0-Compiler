#ifndef FREADC_H
#define FREADC_H

#include "FRead.h"
#include <cstdio>
#include <string>
using namespace std;

class FReadC : public FRead {
private:
	FILE *file;
public:
	FReadC();
	void open(string fpath);
	bool isOpen();
	char getChar();
	~FReadC();
};

#endif