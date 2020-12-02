#pragma once
#include "Building.h"
#include <algorithm>

class Aqueduct :public Building {
private:
public:
	Aqueduct();
	bool isBuildable(std::vector<Technologies> techno) override;
};
