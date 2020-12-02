#pragma once
#include "Terrain.h"
#include "Horses.h"

class Plains :public Terrain {
private:
	Horses horses;
public:
	Plains(int res = 0);
};