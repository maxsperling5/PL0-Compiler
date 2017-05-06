#include "./FReadC.h"

FReadC::FReadC() {
	file = 0;
	strText = "";
}

void FReadC::open(string fpath) {
	file = fopen(fpath.c_str(), "rb");
}

bool FReadC::isOpen() {
	return file != 0 ? true : false;
}

string FReadC::getText() {
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	void *cstr = malloc(fsize + 1);
	fread(cstr, fsize, 1, file);
	strText = (char*)cstr;
	free(cstr);

	return strText;
}

FReadC::~FReadC() {
	fclose(file);
}