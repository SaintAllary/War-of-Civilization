#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class Monarchy :public Technologies {
public:
	Monarchy();
	void checkPrevTech(std::vector<Technologies>& b);
};
