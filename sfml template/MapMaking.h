#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>
class MapMaking :public Technologies {
public:
	MapMaking();
	void checkPrevTech(std::vector<Technologies>& b);
};
