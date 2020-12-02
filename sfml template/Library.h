#pragma once
#include "Building.h"
class Library :public Building {
private:
public:
	Library();
	bool isBuildable(std::vector<Technologies> techno) override;
};
