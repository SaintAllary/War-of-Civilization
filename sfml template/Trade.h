#pragma once
#include <algorithm>
#include <vector>
#include "Technologies.h"

class Trade :public Technologies {
public:
	Trade();
	void checkPrevTech(std::vector<Technologies>& b);
};