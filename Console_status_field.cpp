#include "Console_status_field.h"

Console_status_field::Console_status_field() {
	height = 0;
	width = 0;
}

Console_status_field::Console_status_field(int h, int w) {
	height = h;
	width = w;
	cells.resize(height);
	for (auto& row : cells) {
		row.resize(width);
		for (int i = 0; i < width; i++) {
			row[i] = new Console_cell(celltype::STATUS);
		}
	}
	for (int i = 1; i < width; i++) {
		cells[0][i]->set_type(celltype::HEDGE);
		cells[height - 1][i]->set_type(celltype::HEDGE);
	}
	for (int i = 1; i < height; i++) {
		cells[i][0]->set_type(celltype::VEDGE);
		cells[i][width - 1]->set_type(celltype::VEDGE);
	}
}

void Console_status_field::draw() {
	string field = "";
	for (auto &row : cells) {
		for (auto& cell : row) {
			field += cell->get_drawing();
		}
		field += "\n";
	}
	cout << field << endl;
}