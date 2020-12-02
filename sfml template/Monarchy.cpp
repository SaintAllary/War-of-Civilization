#include "Monarchy.h"

Monarchy::Monarchy() :Technologies("Monarchy", 0, 0) {}

void Monarchy::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Ceremonial Burial" && t.getIsLearned() == true) || (t.getName() == "Alphabet" && t.getIsLearned() == true)) { count++; } });
	count == 2 ? this->canBeBuildiable = 1 : false;
}