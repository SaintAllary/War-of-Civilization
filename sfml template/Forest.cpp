#include "Forest.h"

Forest::Forest(int res) {
	texture.loadFromFile(PATH_TO_TERRAINS_FOREST);
	this->sprite.setTexture(this->texture);
	this->name = "forest";
	this->move = 1;
	this->food = 1;
	this->prodaction = 2;
	this->trade = 0;
	this->defense = 1;

	if (res == 1)
		this->food += this->game.getFood();
}