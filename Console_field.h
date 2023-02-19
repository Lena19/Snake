#pragma once
#include "Field.h"
#include "Console_cell.h"

class Console_field : public Field {
public:
	Console_field();
	Console_field(int w, int h);
	void draw();
	int get_width();
	int get_height();
	void set_cell(int x, int y, celltype ct);
	celltype get_celltype(int x, int y);
	bool spawn_target();
	~Console_field(){}
};