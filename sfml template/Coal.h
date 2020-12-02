#pragma once
#include "Resourses.h"
class Coal : public Resourses {
private:
	int prodaction;
public:
	Coal();

	int getProdaction();
};