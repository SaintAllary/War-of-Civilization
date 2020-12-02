#pragma once
#include "Map.h"
#include "Cavalry.h"
#include "Legion.h"
#include "Militia.h"
#include "Settlers.h"
#include "Aqueduct.h"
#include "Barracks.h"
#include "CityWalls.h"
#include "Library.h"
#include "Marketplace.h"
#include "Chariot.h"

class Town {
private:
	sf::Font font;
	sf::Text populationText;
	sf::Sprite townSprite;
	sf::Texture texture;
	std::string name;
	std::vector<Building>buildings;
	//std::vector<Disasters>disasters;
	int positionX, positionY;
	int health;
	int damage;
	int population;
	int population_limit;
	int production;
	int food;
	int trade;
	int happines;
	int goldIncome;
	int science;
	int playerID;
	void statInfo(sf::RenderWindow& w);
public:
	bool isMenu;
	//=====================================================
	Town(int positionX = 0, int positionY = 0, std::string name = "NoNameTown");

	//functions that can be changed

	///1-Settlers, 2-Militia, 3-Legion, 4-Cavalry, 5-Chariot
	void createUnit(Map& map, int unit, std::vector<Unit>& actor);
	///1-Aqueduct, 2-Barracks, 3-Walls, 4-Lib, 5-Market
	void createBuilding(int building);
	void setColorByID();
	void spawn(int x, int y, Map& map);

	//getters

	int getPositionX();
	int getPositionY();
	int getHealth();
	int getProduction();
	int getGoldIncome();
	int getFood();
	int getTrade();
	int getPopulation();
	int getHappines();
	int getPlayer_id();
	int getPopulation_limit();
	int getScience();
	int getDamage();
	std::string getName();

	//setters

	void setPosition(int x, int y);
	void setHealth(int health);
	void setProduction(int prod);
	void setgoldIncome(int goldIncome);
	void setFood(int food);
	void setTrade(int trade);
	void setPopulation(int population);
	void setHappines(int happines);
	void setPlayer_id(int player_id);
	void setPopulation_limit(int population_limit);
	void setScience(int science);
	void setName(std::string name);
	void setDamage(int damage);

	//needed

	void draw(sf::RenderWindow& w, Map& map);
	void endOfTurn(Map& map, int& gold, int& science);
	std::string getSaveTownInfo();
};