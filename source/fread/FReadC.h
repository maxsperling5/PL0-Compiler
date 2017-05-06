#ifndef FREADC_H
#define FREADC_H

#include "FRead.h"
#include <cstdio>
#include <cstdlib>
using namespace std;

class FReadC : public FRead {
private:
	FILE *file;
	string strText;
public:
	FReadC();
	void open(string fpath);
	bool isOpen();
	string getText();
	~FReadC();
};

#endif