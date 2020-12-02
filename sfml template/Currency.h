#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class Currency :public Technologies {
public:
	Currency();
	void checkPrevTech(std::vector<Technologies>& b);
};
