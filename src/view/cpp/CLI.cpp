#include "../headers/CLI.h"

CLI::CLI(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "Parameter: PL0-Filepath" << endl;
		return;
	}
	fpath = argv[1];
}

void CLI::outStr(string str) {
	cout << str;
}