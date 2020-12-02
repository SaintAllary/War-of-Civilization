#include "Mathematics.h"

Mathematics::Mathematics() : Technologies("Mathematics", 0, 0) {}

void Mathematics::checkPrevTech(std::vector<Technologies>& b) {
	int count = 0;
	std::for_each(b.begin(), b.end(), [&count](Technologies t) { if ((t.getName() == "Masonry" && t.getIsLearned() == true) || (t.getName() == "Alphabet" && t.getIsLearned() == true)) { count++; } });
	count == 2 ? this->canBeBuildiable = 1 : false;
}