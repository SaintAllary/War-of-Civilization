#include "Oil.h"

Oil::Oil() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_OIL);
	this->sprite.setTexture(texture);
	this->prodaction = 4;
}

int Oil::getProdaction() {
	return this->prodaction;
}