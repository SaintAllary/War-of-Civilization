#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

//Нужен алфавит
class Writing :public Technologies {
private:

public:
	Writing();
	void checkPrevTech(std::vector<Technologies>& b);
};
