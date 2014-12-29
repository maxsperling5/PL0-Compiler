#include "../../view/headers/View.h"
#include "../../model/headers/Model.h"

#include "../../view/headers/CLI.h"
#include "../../model/headers/Compiler.h"

int main(int argc, char *argv[])
{
	View *view = new CLI(argc, argv);
	Model *model = new Compiler();

	view->setModel(model);
	model->setView(view);

	return 0;
}