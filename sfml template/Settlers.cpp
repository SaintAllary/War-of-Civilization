#include "Settlers.h"
//name,health,armor,damage,speed,rank,salary,productionPrice,price,index,playerId,maxspeed
Settlers::Settlers() :Unit("Settlers", 1, 0, 1, 3, 0, 0, 40, 320, 1, 0, 3) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(PATH_TO_UNITES_SETTLERS);
	warriorSprite.setTexture(*texture);
}