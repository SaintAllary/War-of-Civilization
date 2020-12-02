#include "Legion.h"

Legion::Legion() :Unit("Legion", 1, 2, 3, 3, 0, 1, 20, 120, 3, 2, 3)
//name,health,armor,damage,speed,rank,salary,productionPrice,price,index,playerId,maxspeed
{
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(PATH_TO_UNITES_LEGION);
	warriorSprite.setTexture(*texture);
}