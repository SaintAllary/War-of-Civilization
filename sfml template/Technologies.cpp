#include "Technologies.h"

Technologies::Technologies(std::string name, bool islearned, bool canBeBuildable) {
	this->name = name;
	this->islearned = islearned;
	this->canBeBuildiable = canBeBuildable;
}

std::string Technologies::getName() {
	return this->name;
}

bool Technologies::getIsLearned() {
	return this->islearned;
}

bool Technologies::getCanBeBuildable() {
	return this->canBeBuildiable;
}

void Technologies::learn() {
	this->islearned = 1;
}

Technologies::~Technologies() {}