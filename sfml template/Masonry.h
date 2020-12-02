#pragma once
#include "Technologies.h"

class Masonry :public Technologies {
public:
	Masonry();
	std::string getName() override;
	bool getIsLearned() override;

	~Masonry();
};
