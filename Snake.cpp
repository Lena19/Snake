#include "Snake.h"

Snake::Snake(int x, int y, Field* f, Cell* c) {
	head_posx = x;
	head_posy = y;
	field = f;
	c->set_type(celltype::SNAKE_HEAD);
	body.resize(0);
	coords.resize(0);
	body.push_back(make_pair(c, direction::RIGHT));
	coords.push_back(make_pair(x, y));
	for (int i = 0; i < 3; i++) grow();
}

void Snake::rotate(direction dir) {
	body[0].second = dir;
}

int Snake::move() {
	auto was_head = coords[0];
	field->set_cell(was_head.first, was_head.second, celltype::SNAKE_BODY);
	auto tail = coords.back();
	field->set_cell(tail.first, tail.second, celltype::EMPTY);
	direction dir = body[0].second;
	switch (dir) {
	case direction::LEFT:
		if (head_posx == 1) {
			return -1;
		}
		head_posx--;
		break;
	case direction::RIGHT:
		if (head_posx == field->get_width() - 1) {
			return -1;
		}
		head_posx++;
		break;
	case direction::UP:
		if (head_posy == 1) {
			return -1;
		}
		head_posy--;
		break;
	case direction::DOWN:
		if (head_posy == field->get_height() - 1) {
			return -1;
		}
		head_posy++;
		break;
	}
	coords[0] = make_pair(head_posx, head_posy);
	if (field->get_celltype(head_posx, head_posy) == celltype::SNAKE_BODY) {
		return -1;
	}
	int cnt = 0;
	if (field->get_celltype(head_posx, head_posy) == celltype::TARGET) {
		grow(); cnt++;
		while (!field->spawn_target()) grow(), cnt++;
	}
	field->set_cell(head_posx, head_posy, celltype::SNAKE_HEAD);
	for (int i = (int)body.size() - 1; i > 0; i--) {
		if (body[i].second == direction::LEFT) {
			coords[i].first--;
		}
		else if (body[i].second == direction::RIGHT) {
			coords[i].first++;
		}
		else if (body[i].second == direction::UP) {
			coords[i].second--;
		}
		else {
			coords[i].second++;
		}
		body[i].second = body[i - 1].second;
	}
	return cnt;
}

void Snake::grow() {
	auto tail = body.back();
	auto tail_coords = coords.back();
	if (tail.second == direction::LEFT) tail_coords.first++;		//add cell in opposite direction
	else if (tail.second == direction::RIGHT) tail_coords.first--;
	else if (tail.second == direction::UP) tail_coords.second++;
	else tail_coords.second--;
	body.push_back(tail);
	coords.push_back(tail_coords);
	//field->set_cell(tail_coords.first, tail_coords.second, celltype::SNAKE_BODY);
}