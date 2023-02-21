#include "Console_cell.h"
#include "Console_status_field.h"
#include <string>

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
	cells[height - 1][width - 1]->set_type(celltype::EMPTY);
}

void Console_status_field::update_info(string s, int val) {
	info[s] = val;
}

void Console_status_field::draw() {
	string field = "";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < width; j++) {
			field += cells[i][j]->get_drawing();
		}
		field += "\n";
	}
	for (auto& s : info) {
		string cur = "";
		for (int i = 0; i < 3; i++) {
			cur += cells[1][i]->get_drawing();
		}
		cur += s.first;
		while (cur.length() % 3 != 0) cur += " ";
		cur += to_string(s.second);
		while (cur.length() != (int)(cells[0].size() - 1) * 3) cur += " ";
		cur += cells[1].back()->get_drawing();
		field += cur;
		field += "\n";
	}
	for (int i = (int)cells.size() - 1; i < (int)cells.size(); i++) {
		for (int j = 0; j < width; j++) {
			field += cells[i][j]->get_drawing();
		}
		field += "\n";
	}
	/*
	for (auto &row : cells) {
		for (auto& cell : row) {
			field += cell->get_drawing();
		}
		field += "\n";
	}
	*/
	cout << field << endl;
}
