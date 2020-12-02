#include "Trade.h"

Trade::Trade() :Technologies("Trade", 0, 0) {}

void Trade::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Currency" && t.getIsLearned() == true) || (t.getName() == "Code of Laws" && t.getIsLearned() == true)) { count++; } });
	count == 2 ? this->canBeBuildiable = 1 : false;
}