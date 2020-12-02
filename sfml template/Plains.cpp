#include "Plains.h"

Plains::Plains(int res) {
	texture.loadFromFile(PATH_TO_TERRAINS_PLAINS);
	this->sprite.setTexture(this->texture);
	this->name = "plains";
	this->move = 1;
	this->food = 1;
	this->prodaction = 1;
	this->trade = 0;
	this->defense = 1;

	if (res == 1)
		this->prodaction += this->horses.getProdaction();
}