#include <../view/hpp/IView.hpp>
#include <../model/hpp/IModel.hpp>
#include <../view/hpp/CLI.hpp>
#include <../model/hpp/Compiler.hpp>

void main(int argc, char* argv[])
{
	IView *view = new CLI();
	IModel *model = new Compiler();
}