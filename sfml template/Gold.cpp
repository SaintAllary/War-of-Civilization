#include "Gold.h"

Gold::Gold() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_GOLD);
	this->sprite.setTexture(texture);
	this->trade = 2;
}

int Gold::getTrade() {
	return this->trade;
}