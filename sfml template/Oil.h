#pragma once
#include "Resourses.h"
class Oil :
	public Resourses {
private:
	int prodaction;
public:
	Oil();

	int getProdaction();
};