#include "../view/View.h"
#include "../comp/Comp.h"
#include "../view/CLI.h"
#include "../comp/CompPL0.h"

int main(int argc, char *argv[]) {
	View *view = new CLI(argc, argv);
	Comp *comp = new CompPL0();

	view->setComp(comp);
	comp->setView(view);

	view->execute();
	return 0;
}