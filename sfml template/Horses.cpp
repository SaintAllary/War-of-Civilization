#include "Horses.h"

Horses::Horses() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_HORSES);
	this->sprite.setTexture(texture);
	this->prodaction = 2;
}

int Horses::getProdaction() {
	return this->prodaction;
}