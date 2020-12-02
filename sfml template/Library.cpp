#include "Library.h"

Library::Library() :Building("Library", 80, 320, -1, 0, 0, 0, 3, 0) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("BuildingsIcons\\Library.png");
	sprite.setTexture(*texture);
}

bool Library::isBuildable(std::vector<Technologies> techno) {
	std::for_each(techno.begin(), techno.end(), [](Technologies tech) { return (tech.getName() == "Writing" && tech.getIsLearned() == true ? true : false); });
}