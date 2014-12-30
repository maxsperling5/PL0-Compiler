#ifndef COMPPL0_H
#define COMPPL0_H

#include "Comp.h"
#include "../../fread/headers/FReadC.h"
#include "../../lexer/headers/LexerPL0.h"

class CompPL0 : public Comp {
private:
public:
	CompPL0();
	void setView(View *view);
	void open(string fpath);
	bool isOpen();	
	void start();
};

#endif