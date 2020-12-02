#pragma once
#include "Terrain.h"
#include "Gold.h"
#include "Oasis.h"

class Mountain :public Terrain {
private:
	Gold gold;
	Oasis oasis;
public:
	Mountain(int res = 0);
};