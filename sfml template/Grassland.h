#pragma once
#include"Terrain.h"
#include "Coal.h"
#include "Horses.h"

class Grassland :public Terrain {
private:
	Coal coal;
	Horses horses;
public:
	Grassland(int res = 0);
};