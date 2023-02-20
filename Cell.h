#pragma once
#include <iostream>

enum class celltype
{
	EMPTY,
	SNAKE_BODY,
	SNAKE_HEAD,
	TARGET,
	VEDGE,
	HEDGE,
	STATUS
};

class Cell {
protected:
	int width, height;
	celltype type;
public:
	Cell(): width(0), height(0), type(celltype::EMPTY) {}
	virtual void set_type(celltype ct) = 0;
	virtual celltype get_type() = 0;
	virtual void draw() = 0;
	virtual std::string get_drawing() = 0;
	virtual ~Cell() {}
};