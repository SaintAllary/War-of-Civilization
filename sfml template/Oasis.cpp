#include "Oasis.h"

Oasis::Oasis() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_OASIS);
	this->sprite.setTexture(texture);
	this->food = 3;
}

int Oasis::getFood() {
	return this->food;
}