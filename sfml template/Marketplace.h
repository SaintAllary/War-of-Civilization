#pragma once
#include "Building.h"
class Marketplace :public Building {
private:
public:
	Marketplace();
	bool isBuildable(std::vector<Technologies> techno) override;
};
