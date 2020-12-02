#include "Militia.h"

Militia::Militia() : Unit("Militia", 1, 0, 1, 3, 0, 0, 10, 50, 2, 1, 3)
//name,health,armor,damage,speed,rank,salary,productionPrice,price,index,playerId,maxspeed
{
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(PATH_TO_UNITES_MILITIA);
	warriorSprite.setTexture(*texture);
}