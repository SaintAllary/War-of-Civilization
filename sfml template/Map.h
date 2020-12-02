#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "Hills.h"
#include "Forest.h"
#include "Mountain.h"
#include "Grassland.h"
#include "Ocean.h"
#include "Plains.h"
#include "Terrain.h"
#include <fstream>
#include "path.h"

class Map {
private:
	std::vector<std::vector<int>> map;
	std::vector<std::vector<int>> units;
public:
	Map(int sizeX = 50, int sizeY = 50, int resGenChanse = 8);

	//CHECKERS
	Terrain getTile(int x, int y);
	Terrain getTileVec(int x, int y);
	bool isTown(int x, int y);
	bool isFog(int x, int y);
	//UNITS
	int getUnitID(int x, int y);
	int getUnitInd(int x, int y);
	int getUnitPlayerID(int x, int y);
	void pushUnit(int x, int y, int unit);
	void moveUnit(int x, int y, int newx, int newy, int unitPlayerID);
	void delUnit(int x, int y);
	//SYSTEM/SAVES
	std::vector<std::vector<int>>& _getVecTerrainsInt();
	std::vector<std::vector<int>>& _getVecUnitsInt();
	void saveMap();
	void loadTerrains(std::string line);
	void loadUnits(std::string line);
	void reTakeTown(int x, int y, int newPlayerID);
	void radarFog(int newx, int newy);
	void __getInfo_DEBUG(int x, int y);
	void getInfo(int x, int y, sf::RenderWindow& w);

	void draw(sf::RenderWindow& w);
};