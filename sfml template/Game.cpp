#include "Game.h"

Game::Game() {
	this->texture.loadFromFile(PATH_TO_RESOURCES_GAME);
	this->sprite.setTexture(texture);
	this->food = 2;
}

int Game::getFood() {
	return this->food;
}