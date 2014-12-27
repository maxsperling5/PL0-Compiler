#include "../../view/headers/IView.h"
#include "../../model/headers/IModel.h"
#include "../../view/headers/CLI.h"
#include "../../model/headers/Compiler.h"

int main(int argc, char* argv[])
{
	IView *view = new CLI();
	IModel *model = new Compiler();

	return 0;
}