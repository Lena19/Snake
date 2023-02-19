
#include "Console_cell.h"
#include <iostream>

Console_cell::Console_cell() {
	width = 3;
	height = 1;
	type = celltype::EMPTY;
}
Console_cell::Console_cell(celltype ct) {
	width = 3;
	height = 1;
	type = ct;
}
void Console_cell::set_type(celltype ct) {
	type = ct;
}
celltype Console_cell::get_type() {
	return type;
}
void Console_cell::draw() {
	switch (type) {
		case celltype::EMPTY:
			printf("__|");
			break;
		case celltype::SNAKE_BODY:
			printf("&&|");
			break;
		case celltype::SNAKE_HEAD:
			printf("^^|");
			break;
		case celltype::TARGET:
			printf("**|");
			break;
		case celltype::HEDGE:
			printf("___");
			break;
		case celltype::VEDGE:
			printf("  |");
			break;
	}
}
std::string Console_cell::get_drawing() {
	switch (type) {
	case celltype::EMPTY:
		return "__|";
	case celltype::SNAKE_BODY:
		return "&&|";
	case celltype::SNAKE_HEAD:
		return "^^|";
	case celltype::TARGET:
		return "**|";
	case celltype::HEDGE:
		return "___";
	case celltype::VEDGE:
		return "  |";
	}
}