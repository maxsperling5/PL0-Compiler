#include "../../view/headers/View.h"
#include "../../comp/headers/Comp.h"
#include "../../view/headers/CLI.h"
#include "../../comp/headers/CompPL0.h"

int main(int argc, char *argv[]) {
	View *view = new CLI(argc, argv);
	Comp *comp = new CompPL0();

	view->setComp(comp);
	comp->setView(view);

	view->execute();
	return 0;
}