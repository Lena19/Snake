#pragma once
#include "Console_field.h"

class Console_status_field : public Console_field {
public:
	Console_status_field();
	Console_status_field(int h, int w);
	void draw();
};