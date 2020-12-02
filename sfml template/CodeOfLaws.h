#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

class CodeOfLaws :public Technologies {
private:
public:
	CodeOfLaws();
	void checkPrevTech(std::vector<Technologies>& b);
};
