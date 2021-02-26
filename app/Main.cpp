/************************/
/* Author: Max Sperling */
/************************/

#include "../src/view/ViewFactory.hpp"
#include "../src/data/DataFactory.hpp"
#include "../src/comp/CompFactory.hpp"

int main(int argc, char *argv[])
{
    pl0compiler::view::IViewUPtr viewUPtr = pl0compiler::view::ViewFactory::create(pl0compiler::view::ViewType::CLI);
    pl0compiler::data::IDataUPtr dataUPtr = pl0compiler::data::DataFactory::create(pl0compiler::data::DataType::File);
    pl0compiler::comp::ICompUPtr compUPtr = pl0compiler::comp::CompFactory::create(pl0compiler::comp::CompType::PL0);

    if (!compUPtr->init(std::move(viewUPtr), std::move(dataUPtr))) return 1;
    if (!compUPtr->exec(argc, argv)) return 2;

    return 0;
}
