#include "Coal.h"

Coal::Coal() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_COAL);
	this->sprite.setTexture(texture);
	this->prodaction = 2;
}

int Coal::getProdaction() {
	return this->prodaction;
}