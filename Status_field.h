#pragma once
#include "Cell.h"
#include <vector>
using namespace std;

class Status_field {
protected:
	int width, height;
	vector<vector<Cell*> > cells;
public:
	virtual void update_info(string s, int val) = 0;
	virtual void draw() = 0;
	virtual ~Status_field() {}
};