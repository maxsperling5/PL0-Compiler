/************************/
/* Author: Max Sperling */
/************************/

#include "./Data/Data.cpp"
#include "./View/View.cpp"
#include "./Lexer/Lexer.cpp"
#include "./Parser/Parser.cpp"

int main(int argc, char *argv[])
{
    View *view = new View();
    if(argc != 2)
    {
		view->writeString("Usage: program \"<filepath/file>\"\n");
		return 1;
	}

    Data *data = new Data();
    data->setPath(argv[1]);
    string code = data->readString();
    view->writeString(code);

    Lexer *lex = new Lexer();
    vector<Token> tok = lex->genToken(code);
    view->writeToken(tok);

    Parser *par = new Parser(tok);
    vector<char> bin = par->genBinary(tok);
    view->writeBinary(bin);
    data->writeBinary(bin);

    //cleanup
    delete lex;
    delete par;

    return 0;
}
