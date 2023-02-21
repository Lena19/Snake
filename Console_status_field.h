#pragma once
#include <unordered_map>
#include "Status_field.h"

class Console_status_field : public Status_field {
	unordered_map<string, int> info;				//info to be shown in the status field
public:
	Console_status_field();
	Console_status_field(int h, int w);
	void update_info(string s, int val);
	void draw();
};