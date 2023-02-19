#pragma once
#include "Cell.h"
#include <vector>
using namespace std;

class Field {
protected:
	int width, height;
	vector<vector<Cell*> > cells;
public:
	virtual int get_width() = 0;
	virtual int get_height() = 0;
	virtual void set_cell(int x, int y, celltype ct) = 0;
	virtual celltype get_celltype(int x, int y) = 0;
	virtual bool spawn_target() = 0;					//return true if the target 
														//was spawned on the empty cell
	virtual void draw() = 0;
	virtual ~Field() {}
};