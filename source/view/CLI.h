#ifndef CLI_H
#define CLI_H

#include "View.h"
#include <iostream>

class CLI : public View {
private:
	string fpath;

	void open(string fpath);
	void start();
public:
	CLI(int argc, char *argv[]);
	void setComp(Comp *comp);
	void execute();
	void outChar(char c);
	void outStr(string str);
};

#endif