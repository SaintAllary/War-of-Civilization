#include "Aqueduct.h"

Aqueduct::Aqueduct() : Building("Aqueduct", 120, 480, 2, 20, 0, 0, 0, 0) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("BuildingsIcons\\Aqueduct.png");
	sprite.setTexture(*texture);
}

bool Aqueduct::isBuildable(std::vector<Technologies> techno) {
	std::for_each(techno.begin(), techno.end(), [](Technologies tech) { return tech.getName() == "Construction" && tech.getIsLearned() == true ? true : false; });
}