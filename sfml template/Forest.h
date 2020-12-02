#pragma once
#include "Terrain.h"
#include "Game.h"

class Forest :public Terrain {
private:
	Game game;
public:
	Forest(int res = 0);
};