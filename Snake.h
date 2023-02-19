#pragma once
#include <vector>
#include "Cell.h"
#include "Field.h"

using namespace std;

enum class direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Snake {
	vector<pair<Cell*, direction>> body;
	vector<pair<int, int>> coords;
	int head_posx, head_posy;
	Field* field;
public:
	Snake(){}
	Snake(int x, int y, Field* f, Cell* c);
	void rotate(direction dir);
	bool move();
	void grow();
};