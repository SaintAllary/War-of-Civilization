#pragma once
#include "Technologies.h"
#include <vector>
#include <algorithm>

//����� �������
class Writing :public Technologies {
private:

public:
	Writing();
	void checkPrevTech(std::vector<Technologies>& b);
};
