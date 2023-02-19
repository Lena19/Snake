#include "Console_field.h"

Console_field::Console_field() {
	width = 0;
	height = 0;
}
Console_field::Console_field(int w, int h) {
	width = w;
	height = h;
	cells.resize(height);
	for (auto& row : cells) {
		row.resize(width);
		for (int i = 0; i < width; i++) {
			row[i] = new Console_cell;
		}
	}
	for (int i = 0; i < cells.size(); i++) {
		if (i != 0) cells[i][0]->set_type(celltype::VEDGE);	//left edge;
		else {
			for (int j = 1; j < cells[0].size(); j++) {
				cells[0][j]->set_type(celltype::HEDGE);			//top edge;
			}
		}
	}
}
int Console_field::get_height() {
	return height;
}
int Console_field::get_width() {
	return width;
}
void Console_field::set_cell(int x, int y, celltype ct) {
	if (0 < x and x <= width and 0 < y and y <= height) {
		cells[y][x]->set_type(ct);
	}
}
celltype Console_field::get_celltype(int x, int y) {
	if (0 < x and x <= width and 0 < y and y <= height) {
		return cells[y][x]->get_type();
	}
	else return celltype::EMPTY;
}
bool Console_field::spawn_target() {
	int posx = rand() % (width - 1) + 1;
	int posy = rand() % (height - 1) + 1;
	celltype ct = get_celltype(posx, posy);
	if (ct == celltype::SNAKE_BODY or ct == celltype::SNAKE_HEAD) {
		return false;
	}
	else {
		set_cell(posx, posy, celltype::TARGET);
		return true;
	}
}
void Console_field::draw() {
	string field_string = "";
	/*for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			if (i == 0 and j == 0) {
				printf("   ");
			}
			else {
				cells[i][j]->draw();
			}
		}
		printf("\n");
	}*/
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			if (i == 0 and j == 0) {
				field_string += "   ";
			}
			else {
				field_string += cells[i][j]->get_drawing();
			}
		}
		field_string += "\n";
	}
	cout << field_string << endl;
}
