#include <string>
#pragma once

class Technologies {
protected:
	std::string name;
	bool islearned;
	bool canBeBuildiable;
public:
	Technologies(std::string name, bool islearned, bool canBeBuildable);
	virtual ~Technologies();
	virtual std::string getName();
	virtual bool getIsLearned();
	virtual bool getCanBeBuildable();
	void learn();
};
