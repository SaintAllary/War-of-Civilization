#include "Masonry.h"

Masonry::Masonry() :Technologies("Masonry", 0, 1) {}

std::string Masonry::getName() {
	return this->name;
}

bool Masonry::getIsLearned() {
	return this->islearned;
}

Masonry::~Masonry() {}