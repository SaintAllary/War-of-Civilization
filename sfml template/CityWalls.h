#pragma once
#include "Building.h"
class CityWalls :public Building {
private:
public:
	CityWalls();
	bool isBuildable(std::vector<Technologies> techno) override;
};
