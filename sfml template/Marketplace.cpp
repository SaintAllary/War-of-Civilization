#include "Marketplace.h"

Marketplace::Marketplace() :Building("Marketplace", 80, 320, 4, 0, 0, 2, 1, 0) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("BuildingsIcons\\Marketplace.png");
	sprite.setTexture(*texture);
}

bool Marketplace::isBuildable(std::vector<Technologies> techno) {
	std::for_each(techno.begin(), techno.end(), [](Technologies tech) { return tech.getName() == "Currency" && tech.getIsLearned() == true ? true : false; });
}