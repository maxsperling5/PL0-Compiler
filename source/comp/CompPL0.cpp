#include "./CompPL0.h"

CompPL0::CompPL0() {
	inp = new FReadC();
	lex = new LexerPL0();
	//par = new Parser();
}

void CompPL0::setView(View *view) {
	this->view = view;
}

void CompPL0::open(string fpath) {
	inp->open(fpath);
}

bool CompPL0::isOpen() {
	return inp->isOpen();
}

void CompPL0::start() {
	if(!inp->isOpen()) return;

	string strSourcecode = inp->getText();
	view->outStr(strSourcecode);
	vector<Token> vecToken = lex->getTokenVec(strSourcecode);
	// tokenvector to parser
	// parser generates machine or intermediate code
	// generated code to filewriter
	// filewriter write binary
}