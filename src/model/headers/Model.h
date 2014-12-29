#ifndef MODEL_H
#define MODEL_H

class View;

#include "../../view/headers/View.h"
#include "../../fread/headers/IFRead.h"
#include "../../lexer/headers/ILexer.h"
#include "../../parser/headers/IParser.h"
#include <string>
using namespace std;

class Model {
private:
protected:
	View *view;

	IFRead *inp;
	ILexer *lex;
	IParser *par;

	string fpath;
public:
	void setView(View *view) {
		this->view = view;
	}

	virtual void start() = 0;
	/*
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void stop() = 0;
	*/
};

#endif