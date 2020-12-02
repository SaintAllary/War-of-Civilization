#include "CityWalls.h"

CityWalls::CityWalls() : Building("City Walls", 120, 480, -2, 0, 0, 0, 1, 5) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("BuildingsIcons\\CityWalls.png");
	sprite.setTexture(*texture);
}

bool CityWalls::isBuildable(std::vector<Technologies> techno) {
	std::for_each(techno.begin(), techno.end(), [](Technologies tech) { return tech.getName() == "Masonry" && tech.getIsLearned() == true ? true : false; });
}