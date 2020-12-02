#include "Mysticism.h"

Mysticism::Mysticism() :Technologies("Mysticism", 0, 0) {}

void Mysticism::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Ceremonial Burial" && t.getIsLearned() == true)) { count++; } });
	count == 1 ? this->canBeBuildiable = 1 : false;
}