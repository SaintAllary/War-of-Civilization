#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class Mysticism :public Technologies {
private:
public:
	Mysticism();
	void checkPrevTech(std::vector<Technologies>& b);
};
