#include "Currency.h"

Currency::Currency() :Technologies("Currency", 0, 0) {}

void Currency::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Bronze Working" && t.getIsLearned() == true)) { count++; } });
	count == 1 ? this->canBeBuildiable = 1 : false;
}