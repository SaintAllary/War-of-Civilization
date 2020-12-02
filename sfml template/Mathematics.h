#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class Mathematics :public Technologies {
protected:
public:
	Mathematics();
	void checkPrevTech(std::vector<Technologies>& b);
};
