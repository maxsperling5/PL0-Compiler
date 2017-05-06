#include "./CLI.h"

CLI::CLI(int argc, char *argv[]) {
	if(argc != 2) {
		outStr("Parameter: PL0-Filepath\n");
		return;
	}
	fpath = argv[1];
}

void CLI::setComp(Comp *comp) {
	this->comp = comp;
}

void CLI::execute() {
	open(fpath);
	if(comp->isOpen()) start();
}

void CLI::open(string fpath) {
	comp->open(fpath);
}

void CLI::start() {
	comp->start();
}

void CLI::outChar(char c) {
	cout << c;
}

void CLI::outStr(string str) {
	cout << str;
}