#include "Barracks.h"

Barracks::Barracks() :Building("Barracks", 40, 160, 0, 0, 1, 0, 0, 0) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("BuildingsIcons\\Barracks.png");
	sprite.setTexture(*texture);
}