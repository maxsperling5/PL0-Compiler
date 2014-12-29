#ifndef COMPILER_H
#define COMPILER_H

#include "Model.h"

#include "../../fread/headers/FRead.h"
#include "../../lexer/headers/Lexer.h"
#include "../../parser/headers/Parser.h"

class Compiler : public Model {
private:
public:
	Compiler();
	void start();
};

#endif