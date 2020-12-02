#include "Mountain.h"

//1=gold, 2=oasis
Mountain::Mountain(int res) {
	texture.loadFromFile(PATH_TO_TERRAINS_MOUNTAIN);
	this->sprite.setTexture(this->texture);
	this->name = "mountain";
	this->move = 3;
	this->food = 2;
	this->prodaction = 1;
	this->trade = 0;
	this->defense = 1;

	if (res == 1) { this->trade += gold.getTrade(); }
	else if (res == 2) { this->food += oasis.getFood(); }
}