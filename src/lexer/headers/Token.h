#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class tokenTyp {
	symbol,
	number,
	identifier,
	keyword,
	string
};

class Token {
private:
	string val;
	tokenTyp typ;
	int srcRow;
	int srcCol;
public:
	Token(int srcRow, int srcCol);
};

#endif