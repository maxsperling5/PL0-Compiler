#ifndef COMP_H
#define COMP_H

class View;

#include "../../view/headers/View.h"
#include "../../fread/headers/FRead.h"
#include "../../lexer/headers/Lexer.h"
#include "../../parser/headers/IParser.h"
#include <string>
using namespace std;

class Comp {
protected:
	View *view;

	FRead *inp;
	Lexer *lex;
	IParser *par;
public:
	virtual void setView(View *view) = 0;

	virtual void open(string fpath) = 0;
	virtual bool isOpen() = 0;
	virtual void start() = 0;
	/*
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void stop() = 0;
	*/
};

#endif