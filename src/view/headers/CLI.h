#ifndef CLI_H
#define CLI_H

#include "View.h"
#include <iostream>

class CLI : public View {
private:
public:
	CLI(int argc, char *argv[]);
	void outStr(string str);
};

#endif