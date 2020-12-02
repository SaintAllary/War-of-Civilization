#include "MapMaking.h"

MapMaking::MapMaking() :Technologies("Map making", 0, 0) {}

void MapMaking::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Alphabet" && t.getIsLearned() == true)) { count++; } });
	count == 1 ? this->canBeBuildiable = 1 : false;
}