#include "Chariot.h"

Chariot::Chariot() :Unit("Chariot", 1, 2, 3, 3, 0, 1, 30, 250, 5, 2, 4)
//name,health,armor,damage,speed,rank,salary,productionPrice,price,index,playerId,maxspeed
{
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(PATH_TO_UNITES_CHARIOT);
	warriorSprite.setTexture(*texture);
}