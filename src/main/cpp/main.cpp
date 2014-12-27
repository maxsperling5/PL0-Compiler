#include "IView.h"
#include "IModel.h"
#include "CLI.h"
#include "Compiler.h"

void main(int argc, char* argv[])
{
	IView *view = new CLI();
	IModel *model = new Compiler();
}