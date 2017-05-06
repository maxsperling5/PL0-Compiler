#ifndef COMP_H
#define COMP_H

class View;

#include "../view/View.h"
#include "../fread/FRead.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"
#include <string>
using namespace std;

class Comp {
protected:
	View *view;

	FRead *inp;
	Lexer *lex;
	Parser *par;
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