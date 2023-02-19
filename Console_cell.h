#pragma once
#include "Cell.h"
#include <iostream>

class Console_cell : public Cell {
public:	
	Console_cell();
	Console_cell(celltype ct);
	void draw();
	void set_type(celltype ct);
	celltype get_type();
	std::string get_drawing();
	~Console_cell() {}
};