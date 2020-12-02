#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class IronWorking :public Technologies {
public:
	void checkPrevTech(std::vector<Technologies>& b);
	IronWorking();
};
