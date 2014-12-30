#include "../headers/FReadC.h"

FReadC::FReadC() {
	file = 0;
}

void FReadC::open(string fpath) {
	file = fopen(fpath.c_str(), "r");
}

bool FReadC::isOpen() {
	return file != 0 ? true : false;
}

char FReadC::getChar() {
	return fgetc(file);
}

FReadC::~FReadC() {
	fclose(file);
}