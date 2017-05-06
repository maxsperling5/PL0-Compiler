#ifndef VIEW_H
#define VIEW_H

class Comp;

#include "../comp/Comp.h"
#include <string>
using namespace std;

class View {
protected:
	Comp *comp;

	virtual void open(string fpath) = 0;
	virtual void start() = 0;
public:
	virtual void setComp(Comp *comp) = 0;
	virtual void execute() = 0;

	virtual void outChar(char c) = 0;
	virtual void outStr(string str) = 0;
};

#endif