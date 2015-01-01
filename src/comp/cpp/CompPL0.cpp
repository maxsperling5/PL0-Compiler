#include "../headers/CompPL0.h"

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

	string str = inp->getStr();
	view->outStr(str);

	//vector<Token> = lex.getToken();
}