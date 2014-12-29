#ifndef VIEW_H
#define VIEW_H

class Model;

#include "../../model/headers/Model.h"
#include <string>
using namespace std;

class View {
private:
protected:
	Model *model;

	string fpath;
public:
	void setModel(Model *model) {
		this->model = model;
	}

	virtual void outStr(string str) = 0;
};

#endif