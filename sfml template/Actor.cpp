#include "Actor.h"

Actor::Actor(std::string name, int playerID) {
	this->playerID = playerID;
	this->name = name;
	//std::vector<std::vector<bool>> fog;
	this->totalGold = 0;
	this->totalScience = 0;
	this->unitController = 0;
	this->townController = 0;
	sf::Texture* tmp = new sf::Texture;
	tmp->loadFromFile(PATH_TO_ICON_TARGET);
	this->target.setTexture(*tmp);
}

void Actor::__SHOW_INFO_DEBUG() {
	std::cout << this->name << std::endl;
	std::cout << this->playerID << std::endl;
	std::cout << this->totalGold << std::endl;
	std::cout << this->totalScience << std::endl;
}

void Actor::__PUSH_UNIT_DEBUG(Unit* unit) { this->units.push_back(*unit); }
void Actor::__PUSH_TOWN_DEBUG(Town* town) { this->towns.push_back(*town); }

bool Actor::takeControl(sf::Event event, Map& map, sf::RenderWindow& w, int& year) {
	//to make camera dynamic
	int mouse_x = sf::Mouse::getPosition(w).x + (w.getView().getCenter().x - w.getSize().x / 2);
	int mouse_y = sf::Mouse::getPosition(w).y + (w.getView().getCenter().y - w.getSize().y / 2);

	//UNIT-MOVE----------

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (event.MouseButtonReleased) {
			if (this->towns.size() > 0) {
				for (int i = 0; i < static_cast<int>(towns.size()); i++) {
					if (this->towns.at(i).getPositionX() == (mouse_x / 32 * 32) && this->towns.at(i).getPositionY() == (mouse_y / 32 * 32)) {
						this->townController = i;
						//std::cout << "\ntownCon " << this->townController;//debug
						if (this->towns.at(townController).isMenu == true)this->towns.at(townController).isMenu = false;
						else this->towns.at(townController).isMenu = true;
						//std::cout << "\nisMenu " << this->towns.at(townController).isMenu;//debug
					}
				}
			}
			map.__getInfo_DEBUG(mouse_x, mouse_y);//DEBUG
		}
	}

	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			//UNIT-TARGET--------
		case sf::Keyboard::Right:
			this->unitController++;

			if (this->unitController >= static_cast<int>(this->units.size()))
				this->unitController = 0;

			break;
			//CREATE-TOWN--------
		case sf::Keyboard::T:
			if (this->units.size() != 0) { //yesn`t hasn`t units
				if (this->units.at(this->unitController).getHealth() > 0) {
					if (this->units.at(this->unitController).getIndex() == 1) { //settlers?
						//std::cout << map.getUnitInd(this->units.at(unitController).getPositionX(), this->units.at(unitController).getPositionY()) << std::endl;//debug
						//map.getTile(this->units.at(unitController).getPositionX(), this->units.at(unitController).getPositionY()).__getInfo_DEBUG();//debug
						if (map.getUnitInd(this->units.at(this->unitController).getPositionX(), this->units.at(this->unitController).getPositionY()) % 100 / 10 == 0) {//no town?
							Town* town = new Town(this->units.at(this->unitController).getPositionX(), this->units.at(this->unitController).getPositionY());
							this->units.at(this->unitController).death(map);
							this->units.erase(this->unitController + this->units.begin());
							town->setPlayer_id(1);
							town->spawn(town->getPositionX(), town->getPositionY(), map);
							this->towns.push_back(*town);

							unitController = 0;
						}
						else std::cout << "<error> this tile already has town\n";
						//std::cout << map.getUnitInd(this->towns.at(0).getPositionX(), this->towns.at(0).getPositionY());//debug
					}
				}
			}

			break;
		case sf::Keyboard::Num1:
			if (this->towns.size() > 0)
				this->towns.at(townController).createUnit(map, 1, this->units);
			break;
		case sf::Keyboard::Num2:
			if (this->towns.size() > 0)
				this->towns.at(townController).createUnit(map, 2, this->units);
			break;
		case sf::Keyboard::Num3:
			if (this->towns.size() > 0)
				this->towns.at(townController).createUnit(map, 3, this->units);
			break;
		case sf::Keyboard::Num4:
			if (this->towns.size() > 0)
				this->towns.at(townController).createUnit(map, 4, this->units);
			break;
		case sf::Keyboard::Num5:
			if (this->towns.size() > 0)
				this->towns.at(townController).createUnit(map, 5, this->units);
			break;
		case sf::Keyboard::A:
			if (this->towns.size() > 0)
				this->towns.at(townController).createBuilding(1);
			break;
		case sf::Keyboard::B:
			if (this->towns.size() > 0)
				this->towns.at(townController).createBuilding(2);
			break;
		case sf::Keyboard::W:
			if (this->towns.size() > 0)
				this->towns.at(townController).createBuilding(3);
			break;
		case sf::Keyboard::L:
			if (this->towns.size() > 0)
				this->towns.at(townController).createBuilding(4);
			break;
		case sf::Keyboard::M:
			if (this->towns.size() > 0)
				this->towns.at(townController).createBuilding(5);
			break;
		case sf::Keyboard::Enter:
			year += 5;
			std::cout << "\nTurn ended!" << std::endl;
			endOfTurn(map);
			return 1;
			break;
		}
	}
	return 0;
}

void Actor::draw(sf::RenderWindow& w, Map& map) {
	//TOWNS-DRAW
	for (auto i : this->towns) {
		i.draw(w, map);
	}
	//UNITS-DRAW
	for (auto i : this->units) {
		i.draw(w, map);
	}

	if (units.size() > 0 && this->playerID == 1) {
		target.setPosition(units.at(unitController).getSprite().getPosition());
		w.draw(target);
	}
}

void Actor::takeTax() {
	for (auto i : this->towns) {
		this->totalGold += i.getGoldIncome();
		this->totalScience += i.getScience();
	}
}

void Actor::pushbackEnemyID(int ID) {
	this->enemyListID.push_back(ID);
}

bool Actor::didLose() {
	if (this->units.size() > 0 || this->towns.size() > 0)
		return false;
	else
		return true;
}

void Actor::takeControlUnit(sf::Event event, Map& map, sf::RenderWindow& w, Actor& actorEnemy) {
	//CHECK IS VECTOR EMTPY
	if (this->units.size() > 0) {
		//===================================================================VARIABLES
		//Dynamic pos for mouse
		int mouse_x = sf::Mouse::getPosition(w).x + (w.getView().getCenter().x - w.getSize().x / 2);
		int mouse_y = sf::Mouse::getPosition(w).y + (w.getView().getCenter().y - w.getSize().y / 2);
		//Pos for unit
		int UnPosX = this->units.at(this->unitController).getPositionX();
		int UnPosY = this->units.at(this->unitController).getPositionY();
		//===================================================================

		//CHECK IS UNIT ALIVE
		if (this->units.at(this->unitController).getHealth() > 0) {
			/*this->units.at(this->unitController).GET_SHOW_INFO_DEBUG();*/
			//top
			//check position of mouse
			if (((mouse_x <= UnPosX + BORDER_PIXEL_60 && mouse_x >= UnPosX + BORDER_PIXEL_30) && (mouse_y >= UnPosY && mouse_y <= UnPosY + BORDER_PIXEL_30))) {
				//Check does can unit go on tile
				if (map.getTile(mouse_x, mouse_y).getMove() <= this->units.at(this->unitController).getSteps()) {
					if ((map.getUnitInd(mouse_x, mouse_y)) % 100 != 0 && (map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 != 5)//check index of unit to attack
						checkIsEnemy(mouse_x, mouse_y, map, actorEnemy.getUnitsVec(), w, 1);//try to attack if it's enemy
					else if ((map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 == 5 && !(map.getTile(mouse_x, mouse_y).isWater()))
						unitAttackTown(mouse_x, mouse_y, map, actorEnemy.getTownsLink(), w, 1);
					if ((map.getUnitInd(mouse_x, mouse_y)) == 0 && !(map.getTile(mouse_x, mouse_y).isWater()))//check is tile empty
						this->units.at(this->unitController).moveRightHidden(map, mouse_x, mouse_y);//move to this position if empty;
				}
			}
			//left
			//check position of mouse
			else if (((mouse_x >= UnPosX - BORDER_PIXEL_30 && mouse_x <= UnPosX) && (mouse_y >= UnPosY && mouse_y <= UnPosY + BORDER_PIXEL_30))) {
				//Check does can unit go on tile
				if (map.getTile(mouse_x, mouse_y).getMove() <= this->units.at(this->unitController).getSteps()) {
					if ((map.getUnitInd(mouse_x, mouse_y)) % 100 != 0 && (map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 != 5)//check index of unit to attack
						checkIsEnemy(mouse_x, mouse_y, map, actorEnemy.getUnitsVec(), w, 2);//try to attack if it's enemy
					else if ((map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 == 5 && !(map.getTile(mouse_x, mouse_y).isWater()))
						unitAttackTown(mouse_x, mouse_y, map, actorEnemy.getTownsLink(), w, 2);
					if ((map.getUnitInd(mouse_x, mouse_y)) == 0 && !(map.getTile(mouse_x, mouse_y).isWater()))//check is tile empty
						this->units.at(this->unitController).moveLeftHidden(map, mouse_x, mouse_y);//move to this position if empty;
				}
			}
			else if ((mouse_y >= UnPosY - BORDER_PIXEL_30 && mouse_y <= UnPosY) && (mouse_x >= UnPosX && mouse_x <= UnPosX + BORDER_PIXEL_30))//check position of mouse
			{
				//Check does can unit go on tile
				if (map.getTile(mouse_x, mouse_y).getMove() <= this->units.at(this->unitController).getSteps()) {
					if ((map.getUnitInd(mouse_x, mouse_y)) % 100 != 0 && (map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 != 5)//check index of unit to attack
						checkIsEnemy(mouse_x, mouse_y, map, actorEnemy.getUnitsVec(), w, 3);//try to attack if it's enemy
					else if ((map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 == 5 && !(map.getTile(mouse_x, mouse_y).isWater()))
						unitAttackTown(mouse_x, mouse_y, map, actorEnemy.getTownsLink(), w, 3);
					if ((map.getUnitInd(mouse_x, mouse_y)) == 0 && !(map.getTile(mouse_x, mouse_y).isWater()))//check is tile empty
						this->units.at(this->unitController).moveTopHidden(map, mouse_x, mouse_y);//move to this position if empty;
				}
			}
			else if ((mouse_y <= UnPosY + BORDER_PIXEL_60 && mouse_y >= UnPosY + BORDER_PIXEL_30) && (mouse_x >= UnPosX && mouse_x <= UnPosX + BORDER_PIXEL_30))//check position of mouse
			{
				if (map.getTile(mouse_x, mouse_y).getMove() <= this->units.at(this->unitController).getSteps()) {
					if ((map.getUnitInd(mouse_x, mouse_y)) % 100 != 0 && (map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 != 5)//check index of unit to attack
						checkIsEnemy(mouse_x, mouse_y, map, actorEnemy.getUnitsVec(), w, 4);//try to attack if it's enemy
					else if ((map.getUnitInd(mouse_x, mouse_y)) / 10 % 10 == 5 && !(map.getTile(mouse_x, mouse_y).isWater()))
						unitAttackTown(mouse_x, mouse_y, map, actorEnemy.getTownsLink(), w, 4);
					if ((map.getUnitInd(mouse_x, mouse_y)) == 0 && !(map.getTile(mouse_x, mouse_y).isWater()))//check is tile empty
						this->units.at(this->unitController).moveDownHidden(map, mouse_x, mouse_y);//move to this position if empty;
				}
			}
			this->units.at(this->unitController).checkUpUnit();
		}
		//if not alive remove it
		else {
			//erase from unit vector
			this->units.erase(this->unitController + this->units.begin());
			//set unit controll to 0
			this->unitController = 0;
		}
	}
}

void Actor::endOfTurnBot(Map& map, Actor& eActor) {
	//to save coordination
	int x = 0;
	int y = 0;

	for (int i = 0; i < this->units.size(); i++) {
		//to save coordination
		x = this->units.at(i).getSprite().getPosition().x;
		y = this->units.at(i).getSprite().getPosition().y;

		int tmp = rand() % 4 + 1;
		//Is alive
		if (this->units.at(i).getHealth() > 0) {
			//right
			if (tmp == 1) {
				//check does can move
				if (map.getTile(x + BORDER_PIXEL_32, y).getMove() < this->units.at(i).getSteps()) {
					for (int j = units[i].getSteps(); j >= 0;) {
						//Is water is tile empty
						if ((map.getUnitInd(x + BORDER_PIXEL_32, y)) == 0 && !(map.getTile(x + BORDER_PIXEL_32, y).isWater())) {
							if (!(map.getTile(x + BORDER_PIXEL_32, y).getMove() < this->units.at(i).getSteps()))
								break;
							this->units.at(i).moveRightHidden(map);
							x += 32;
							j = units[i].getSteps();
						}
						//is enemy
						else if (map.getUnitInd(x + BORDER_PIXEL_32, y) % 10 != 0 && map.getUnitPlayerID(x + BORDER_PIXEL_32, y) == 1) {
							for (auto& k : eActor.getUnits()) {
								if (k.getPositionX() == x + BORDER_PIXEL_32, k.getPositionY() == y) {
									this->units[i].attack(k, map, x + BORDER_PIXEL_32, y);
									break;
								}
							}
							break;
						}
						//is town
						else if (map.getUnitInd(x + BORDER_PIXEL_32, y) / 10 % 10 == 5 && map.getUnitPlayerID(x + BORDER_PIXEL_32, y) == 1) {
							botAttackTown(map, eActor, x, y, i, 1);
							break;
						}
						else
							break;
					}
				}
			}
			//left
			if (tmp == 2) {
				//check does can move
				if (map.getTile(x - BORDER_PIXEL_32, y).getMove() < this->units.at(i).getSteps()) {
					for (int j = units[i].getSteps(); j >= 0;) {
						//Is water
						if ((map.getUnitInd(x - BORDER_PIXEL_32, y)) == 0 && !(map.getTile(x - BORDER_PIXEL_32, y).isWater())) {
							if (!(map.getTile(x - BORDER_PIXEL_32, y).getMove() < this->units.at(i).getSteps()))
								break;
							this->units.at(i).moveLeftHidden(map);
							x -= BORDER_PIXEL_32;
							j = units[i].getSteps();
						}
						//is enemy
						else if (map.getUnitInd(x - BORDER_PIXEL_32, y) % 10 != 0 && map.getUnitPlayerID(x - BORDER_PIXEL_32, y) == 1) {
							for (auto& k : eActor.getUnits()) {
								if (k.getPositionX() == x - BORDER_PIXEL_32, k.getPositionY() == y) {
									this->units[i].attack(k, map, x - 32, y);
									break;
								}
							}
							break;
						}
						//is town
						else if (map.getUnitInd(x - BORDER_PIXEL_32, y) / 10 % 10 == 5 && map.getUnitPlayerID(x - BORDER_PIXEL_32, y) == 1) {
							botAttackTown(map, eActor, x, y, i, 2);
							break;
						}

						else
							break;
					}
				}
			}
			//top
			if (tmp == 3) {
				//check does can move
				if (map.getTile(x, y - BORDER_PIXEL_32).getMove() < this->units.at(i).getSteps()) {
					for (int j = units[i].getSteps(); j >= 0;) {
						//Is water
						if ((map.getUnitInd(x, y - BORDER_PIXEL_32)) == 0 && !(map.getTile(x, y - BORDER_PIXEL_32).isWater())) {
							if (!(map.getTile(x, y - BORDER_PIXEL_32).getMove() < this->units.at(i).getSteps()))
								break;
							this->units.at(i).moveTopHidden(map);
							y -= 32;
							j = units[i].getSteps();
						}
						//is enemy
						else if (map.getUnitInd(x, y - BORDER_PIXEL_32) % 10 != 0 && map.getUnitPlayerID(x, y - BORDER_PIXEL_32) == 1) {
							for (auto& k : eActor.getUnits()) {
								if (k.getPositionX() == x, k.getPositionY() == y - 32) {
									this->units[i].attack(k, map, x, y - BORDER_PIXEL_32);
									break;
								}
							}
							break;
						}
						//is town
						else if (map.getUnitInd(x, y - BORDER_PIXEL_32) / 10 % 10 == 5 && map.getUnitPlayerID(x, y - BORDER_PIXEL_32) == 1) {
							botAttackTown(map, eActor, x, y, i, 3);
							break;
						}

						else
							break;
					}
				}
			}
			////down
			if (tmp == 4) {
				//check does can move
				if (map.getTile(x, y + BORDER_PIXEL_32).getMove() < this->units.at(i).getSteps()) {
					for (int j = units[i].getSteps(); j >= 0;) {
						//Is water
						if ((map.getUnitInd(x, y + BORDER_PIXEL_32)) == 0 && !(map.getTile(x, y + BORDER_PIXEL_32).isWater())) {
							if (!(map.getTile(x, y + BORDER_PIXEL_32).getMove() < this->units.at(i).getSteps()))
								break;
							this->units.at(i).moveDownHidden(map);
							y += BORDER_PIXEL_32;
							j = units[i].getSteps();
						}
						//is enemy
						else if (map.getUnitInd(x, y + BORDER_PIXEL_32) % 10 != 0 && map.getUnitPlayerID(x, y + BORDER_PIXEL_32) == 1) {
							for (auto& k : eActor.getUnits()) {
								if (k.getPositionX() == x, k.getPositionY() == y + BORDER_PIXEL_32) {
									this->units[i].attack(k, map, x, y + BORDER_PIXEL_32);
									break;
								}
							}
							break;
						}
						//is town
						else if (map.getUnitInd(x, y + BORDER_PIXEL_32) / 10 % 10 == 5 && map.getUnitPlayerID(x, y + BORDER_PIXEL_32) == 1) {
							botAttackTown(map, eActor, x, y, i, 4);
							break;
						}
						else
							break;
					}
				}
			}
		}
		else {
			this->units.erase(units.begin() + i);
		}
	}

	bool have_s = 0;
	for (int i = 0; i < units.size(); i++) {
		if (this->units[i].getIndex() == 1) {
			unitController = i;
			have_s = 1;
		}
		else have_s = 0;
	}
	if (have_s) {
		if (!(rand() % 10)) {
			if (this->units.size() > 0) {
				if (this->units.at(this->unitController).getHealth() > 0) {
					if (this->units.at(this->unitController).getIndex() == 1) {
						//std::cout << map.getUnitInd(this->units.at(unitController).getPositionX(), this->units.at(unitController).getPositionY()) << std::endl;//debug
						//map.getTile(this->units.at(unitController).getPositionX(), this->units.at(unitController).getPositionY()).__getInfo_DEBUG();//debug
						if (map.getUnitInd(this->units.at(this->unitController).getPositionX(), this->units.at(this->unitController).getPositionY()) % 100 / 10 == 0) {
							Town* town = new Town(this->units.at(this->unitController).getPositionX(), this->units.at(this->unitController).getPositionY());
							this->units.at(this->unitController).death(map);
							this->units.erase(this->unitController + this->units.begin());
							town->setPlayer_id(this->playerID);
							town->spawn(town->getPositionX(), town->getPositionY(), map);
							this->towns.push_back(*town);
							this->unitController = 0;
						}
						else std::cout << "BOT CAN'T CREATE TOWN";
						//std::cout << map.getUnitInd(this->towns.at(0).getPositionX(), this->towns.at(0).getPositionY());//debug
					}
				}
			}
		}
	}

	//Train units
	for (int i = 0; i < static_cast<int>(towns.size()); i++) {
		if (towns[i].getPopulation() > 2 && towns[i].getProduction() > 40) {
			towns[i].createUnit(map, 1, this->units);
		}
		if (towns[i].getProduction() > 40) {
			int unitChoise = rand() % 3 + 2;
			towns[i].createUnit(map, unitChoise, this->units);
		}
	}
	//End of turns
	for (int i = 0; i < static_cast<int>(towns.size()); i++) {
		towns[i].endOfTurn(map, this->totalGold, this->totalScience);
	}
	for (int i = 0; i < static_cast<int>(units.size()); i++) {
		units.at(i).recharge();
	}
}

void Actor::botAttackTown(Map& map, Actor& eActor, int x, int y, int i, int direction) {
	if (direction == 1)
		x += BORDER_PIXEL_32;
	else if (direction == 2)
		x -= BORDER_PIXEL_32;
	else if (direction == 3)
		y -= BORDER_PIXEL_32;
	else if (direction == 4)
		y += BORDER_PIXEL_32;

	int time = 0;
	for (auto j : eActor.getTownsLink()) {
		if (j.getPositionX() == (x) / BORDER_PIXEL_32 * BORDER_PIXEL_32 && j.getPositionY() == (y) / BORDER_PIXEL_32 * BORDER_PIXEL_32)//find enemy in enemy vector
		{
			//damage to town
			if (this->units.at(i).getDamage() - map.getTile(x, y).getDefense() > 0) {
				//if damage more than defense it will attack on full damage- defense
				//eActor.getTownsLink().at(time).setHealth(eActor.getTownsLink().at(time).getHealth() - (this->units.at(i).getDamage() - map.getTile(x, y).getDefense()));
				eActor.getTownsLink().at(time).setHealth(eActor.getTownsLink().at(time).getHealth() - ((this->units.at(i).getDamage() + BOT_DAMAGE_MOD)));
			}
			else {
				//if damage is less than armor you will damage only 1
				/*eActor.getTownsLink().at(time).setHealth(eActor.getTownsLink().at(time).getHealth() - 1);*/
				eActor.getTownsLink().at(time).setHealth(eActor.getTownsLink().at(time).getHealth() - (this->units.at(i).getDamage() + BOT_DAMAGE_MOD));
			}

			if (this->units.at(this->unitController).getArmor() <= 0)
				this->units.at(i).setHealth(this->units.at(i).getHealth() - (eActor.getTownsLink().at(time).getDamage()) - this->units.at(i).getArmor());
			else
				this->units.at(i).setArmor(this->units.at(i).getArmor() - eActor.getTownsLink().at(time).getDamage());

			if (eActor.getTownsLink().at(time).getHealth() <= 0) {
				//change town type
				eActor.getTownsLink()[time].setPlayer_id(this->playerID);
				eActor.getTownsLink()[time].setColorByID();
				eActor.getTownsLink()[time].setHealth(10);
				//give unit to player
				this->towns.push_back(eActor.getTownsLink()[time]);
				//take from enemy
				eActor.getTownsLink().erase(eActor.getTownsLink().begin() + time);
				// to change on map
				map.reTakeTown(x, y, this->playerID);
			}

			if (this->units.at(i).getHealth() <= 0)
				this->units.at(i).death(map);

			break;
		}
		time++;
	}
}

#pragma region GETTERS
int Actor::getPlayerID() {
	return this->playerID;
}

std::vector<int> Actor::getEnemyListID() {
	return this->enemyListID;
}

std::vector<int> Actor::getAlliesListID() {
	return this->alliesListID;
}

std::string Actor::getName() {
	return this->name;
}

std::vector<Town> Actor::getTowns() {
	return this->towns;
}

std::vector<Town>& Actor::getTownsLink() {
	return this->towns;
}

std::vector<Unit>& Actor::getUnits() {
	return this->units;
}

std::vector<Technologies> Actor::getTech() {
	return this->tech;
}

std::vector<Unit>& Actor::getUnitsVec() {
	return this->units;
}

int Actor::getTotalGold() {
	return this->totalGold;
}

int Actor::getTotalScience() {
	return this->totalScience;
}

#pragma endregion

#pragma region SETTERS
void Actor::setPlayerID(int playerID) {
	this->playerID = playerID;
}

void Actor::setTotalGold(int totalGold) {
	this->totalGold = totalGold;
}

void Actor::setTotalScience(int totalScience) {
	this->totalScience = totalScience;
}

void Actor::setUnitVector(std::vector<Unit> units) {
	this->units = units;
}

void Actor::setUnitTown(std::vector<Town> towns) {
	this->towns = towns;
}

#pragma endregion

void Actor::endOfTurn(Map& map) {
	for (int i = 0; i < static_cast<int>(towns.size()); i++) {
		towns[i].endOfTurn(map, this->totalGold, this->totalScience);
	}
	for (int i = 0; i < static_cast<int>(units.size()); i++) {
		units.at(i).recharge();
	}
}

void Actor::saveUnits() {
	std::string path = PATH_TO_SAVE_1;
	std::ofstream fout;
	fout.open(path, std::ofstream::app);
	if (!fout.is_open())
		std::cout << "Error, file wasn't opened" << std::endl;
	else {
		for (auto i : units) {
			fout << i.getSaveUnitInfo();
		}
		fout << "\n#\n";
	}
	fout.close();
}

void Actor::saveTowns() {
	std::string path = PATH_TO_SAVE_1;
	std::ofstream fout;
	fout.open(path, std::ofstream::app);
	if (!fout.is_open())
		std::cout << "Error, file wasn't opened" << std::endl;
	else {
		for (auto i : towns) {
			fout << i.getSaveTownInfo();
			fout << "\n*\n";
		}
		fout << "\n&\n";
	}
	fout.close();
}

std::string Actor::getSaveActorInfo() {
	std::string unitInfo;
	unitInfo += this->name;
	unitInfo += " ";
	unitInfo += std::to_string(this->playerID);
	unitInfo += " ";
	unitInfo += std::to_string(this->totalGold);
	unitInfo += " ";
	unitInfo += std::to_string(this->totalScience);
	unitInfo += "\n_\n";
	return unitInfo;
}

void Actor::saveActorInfo() {
	std::string path = PATH_TO_SAVE_1;
	std::ofstream fout;
	fout.open(path, std::ofstream::app);
	if (!fout.is_open())
		std::cout << "Error, file wasn't opened" << std::endl;
	else {
		fout << getSaveActorInfo();
	}

	fout.close();
}

void Actor::saveTotalnfo() {
	saveActorInfo();
	saveTowns();
	saveUnits();
}

void Actor::checkIsEnemy(int mouse_x, int mouse_y, Map& map, std::vector<Unit>& enemies, sf::RenderWindow& w, int direction) {
	int time = 0;//variable that show which unit you need to attack
	bool tmp = true;
	for (auto i : this->enemyListID)//try to find enemy in enemy vector
	{
		if (i == (map.getUnitInd(mouse_x, mouse_y) / 100))//compare id of all players and enemies id
		{
			for (auto j : enemies)//
			{
				if (j.getIndex() == (map.getUnitInd(mouse_x, mouse_y) % 100) && (j.getPositionX() == mouse_x / 32 * 32 && j.getPositionY() == mouse_y / 32 * 32))//find enemy in enemy vector
				{
					tmp = false;
					this->units.at(unitController).attack(enemies.at(time), map, mouse_x, mouse_y);//attack him
					this->units.at(unitController).animationOfAttack(direction, w, map);
					break;
				}
				time++;
			}
			break;
		}
	}
	if (map.getUnitInd(mouse_x, mouse_y) / 100 != this->playerID && map.getUnitInd(mouse_x, mouse_y) != 0 && tmp == true) {
		enemyListID.push_back(map.getUnitInd(mouse_x, mouse_y) / 100);
		std::cout << "YOU START WAR" << std::endl;
		std::cout << map.getUnitInd(mouse_x, mouse_y) / 100 << std::endl;
	}
}

void Actor::unitAttackTown(int mouse_x, int mouse_y, Map& map, std::vector<Town>& townsEnemy, sf::RenderWindow& w, int direction) {
	int time = 0;//variable that show which unit you need to attack
	bool tmp = true;
	bool isEnemy = false;
	for (auto i : this->enemyListID)//try to find enemy in enemy vector
	{
		if (i == (map.getUnitInd(mouse_x, mouse_y) / 100))//compare id of all players and enemies id
		{
			isEnemy = true;
			for (auto j : townsEnemy) {
				if (j.getPositionX() == mouse_x / 32 * 32 && j.getPositionY() == mouse_y / 32 * 32)//find enemy in enemy vector
				{
					//animation
					this->units.at(this->unitController).animationOfAttack(direction, w, map);
					//damage to town
					if (this->units.at(this->unitController).getDamage() - map.getTile(mouse_x, mouse_y).getDefense() > 0) {
						//if damage more than defense it will attack on full damage- defense
						townsEnemy.at(time).setHealth(townsEnemy.at(time).getHealth() - (this->units.at(this->unitController).getDamage() - map.getTile(mouse_x, mouse_y).getDefense()));
					}
					else {
						//if damage is less than armor you will damage only 1
						townsEnemy.at(time).setHealth(townsEnemy.at(time).getHealth() - 1);
					}

					if (this->units.at(this->unitController).getArmor() <= 0) {
						this->units.at(this->unitController).setHealth(this->units.at(this->unitController).getHealth() - (townsEnemy.at(time).getDamage()) - this->units.at(this->unitController).getArmor());
					}
					else
						this->units.at(this->unitController).setArmor(this->units.at(this->unitController).getArmor() - townsEnemy.at(time).getDamage());

					if (townsEnemy.at(time).getHealth() <= 0) {
						//change town type
						townsEnemy[time].setPlayer_id(1);
						townsEnemy[time].setColorByID();
						townsEnemy[time].setHealth(10);
						//give unit to player
						this->towns.push_back(townsEnemy[time]);
						//take from enemy
						townsEnemy.erase(townsEnemy.begin() + time);
						// to change on map
						map.reTakeTown(mouse_x, mouse_y, this->playerID);
					}

					if (this->units.at(this->unitController).getHealth() <= 0) {
						this->units.at(this->unitController).death(map);
					}

					tmp = false;
					break;
				}
				time++;
			}
			break;
		}
	}
	if (map.getUnitInd(mouse_x, mouse_y) / 100 != this->playerID && map.getUnitInd(mouse_x, mouse_y) != 0 && tmp == true) {
		if (isEnemy == false)
			enemyListID.push_back(map.getUnitInd(mouse_x, mouse_y) / 100);

		std::cout << "YOU START WAR (TOWN)" << std::endl;
		std::cout << "With player: " << map.getUnitInd(mouse_x, mouse_y) / 100 << std::endl;
	}
}