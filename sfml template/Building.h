#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Technologies.h"

class Building {
protected:
	std::string name;
	sf::Sprite sprite;
	//prices:
	int productionPrice;
	int goldCost;
	int goldPerTurn;
	//player info
	int incraiseLimit;
	int rankMultiplier;
	int moneyMultiplier;
	int scienceMultiplier;
	int increaseHP;
public:
	Building(std::string, int productionPrice, int goldCost, int goldPerTurn,
		int incraseLimit, int rankMulti, int moneyMulti, int scieceMulti, int increaseHP);
	//getters
	std::string getName();
	int getProductionPrice();
	int getGoldCost();
	int getgoldPerTurn();
	int getIncraiseLimit();
	int getRankMultiplier();
	int getMoneyMultiplier();
	int getScienceMultiplier();
	int getIncreaseHP();
	int getSellValue();
	//setters
	void setProductionPrice(int productionPrice);
	void setGoldCost(int GoldCost);
	void setGoldPerTurn(int GoldPerTurn);
	void setIncraiseLimit(int IncraiseLim);
	void setRankMultiplier(int RankMultiplier);
	void setMoneyMultiplier(int MoneyMultiplier);
	void setScienceMultiplier(int ScienceMultiplier);
	void setIncreaseHp(int IncreaseHp);
	//methods
	virtual bool isBuildable(std::vector<Technologies> techno);

	//destructor
	~Building();
};
