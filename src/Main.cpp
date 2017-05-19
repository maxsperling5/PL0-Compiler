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
		view->writeString("Parameter: Filepath\n");
		return 1;
	}

    Data *data = new Data();
    string code = data->readString(argv[1]);
    view->writeString(code);

    Lexer *lex = new Lexer();
    vector<Token> tok = lex->genToken(code);
    view->writeToken(tok);

    Parser *par = new Parser(tok);
    vector<uint8_t> bin = par->genBinary(tok);
    view->writeBinary(bin);
    data->writeBinary(bin);

    //cleanup
    delete lex;
    delete par;

    return 0;
}
