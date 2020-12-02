#include "Building.h"

Building::Building(std::string name, int productionPrice, int goldCost, int goldPerTurn, int incraseLimit, int rankMulti, int moneyMulti, int scieceMulti, int increaseHP) {
	this->name = name;
	this->productionPrice = productionPrice;
	this->goldCost = goldCost;
	this->goldPerTurn = goldPerTurn;
	this->incraiseLimit = incraseLimit;
	this->rankMultiplier = rankMulti;
	this->moneyMultiplier = moneyMulti;
	this->scienceMultiplier = scieceMulti;
	this->increaseHP = increaseHP;
}

std::string Building::getName() {
	return this->name;
}

int Building::getProductionPrice() {
	return this->productionPrice;
}

int Building::getGoldCost() {
	return this->goldCost;
}

int Building::getgoldPerTurn() {
	return this->goldPerTurn;
}

int Building::getIncraiseLimit() {
	return this->incraiseLimit;
}

int Building::getRankMultiplier() {
	return this->rankMultiplier;
}

int Building::getMoneyMultiplier() {
	return this->moneyMultiplier;
}

int Building::getScienceMultiplier() {
	return this->scienceMultiplier;
}

int Building::getIncreaseHP() {
	return this->increaseHP;
}

int Building::getSellValue() {
	return this->goldCost / 4;
}

void Building::setProductionPrice(int productionPrice) {
	this->productionPrice = productionPrice;
}

void Building::setGoldCost(int GoldCost) {
	this->goldCost = GoldCost;
}

void Building::setGoldPerTurn(int GoldPerTurn) {
	this->goldPerTurn = goldPerTurn;
}

void Building::setIncraiseLimit(int IncraiseLim) {
	this->incraiseLimit = IncraiseLim;
}

void Building::setRankMultiplier(int RankMultiplier) {
	this->rankMultiplier = RankMultiplier;
}

void Building::setMoneyMultiplier(int MoneyMultiplier) {
	this->moneyMultiplier = MoneyMultiplier;
}

void Building::setScienceMultiplier(int ScienceMultiplier) {
	this->scienceMultiplier = ScienceMultiplier;
}

void Building::setIncreaseHp(int IncreaseHp) {
	this->increaseHP = IncreaseHp;
}

bool Building::isBuildable(std::vector<Technologies> techno) {
	return true;
}

Building::~Building() {}