#include "Town.h"

Town::Town(int positionX, int positionY, std::string name) {
	this->texture.loadFromFile(PATH_TO_ICON_TOWN);
	this->townSprite.setTexture(texture);
	this->positionX = positionX;
	this->positionY = positionY;
	this->townSprite.setPosition(static_cast<float>(positionX), static_cast<float>(positionY));
	this->font.loadFromFile("18536.ttf");
	this->populationText.setCharacterSize(25);
	this->populationText.setFont(this->font);
	this->populationText.setPosition(static_cast<float>(this->positionX + 10), static_cast<float>(positionY));
	this->name = name;
	this->health = 10;
	this->damage = 1;
	this->production = 0;
	this->goldIncome = 0;
	this->food = 5;
	this->population = 1;
	this->population_limit = 10;
	this->happines = 100;
	this->playerID = 1;//debug
	this->science = 0;
	this->isMenu = 0;//debug
}

void Town::createUnit(Map& map, int unit, std::vector<Unit>& actor) {
	Settlers* settlers = new Settlers();
	Militia* militia = new Militia();
	Legion* legion = new Legion();
	Cavalry* cavalry = new Cavalry();
	Chariot* chariot = new Chariot();
	for (auto i : this->buildings) {
		settlers->setRank(i.getRankMultiplier());
		militia->setRank(i.getRankMultiplier());
		legion->setRank(i.getRankMultiplier());
		cavalry->setRank(i.getRankMultiplier());
		chariot->setRank(i.getRankMultiplier());
	}
	switch (unit) {
	case 1:
		if (this->production >= settlers->getProductionPrice()) {
			if (map.getUnitInd(positionX, positionY) % 10 == 0) {
				if (population > 1) {
					this->production -= settlers->getProductionPrice();
					settlers->setPlayerID(this->playerID);
					settlers->spawn(positionX, positionY, map);
					actor.push_back(*settlers);
					this->population--;
				}
				else std::cout << "<error> no humans in town(need >1)\n";
			}
			else
				std::cout << "<error> no space under the town;\n";
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << settlers->getProductionPrice() << ")\n";
		break;
	case 2:
		if (this->production >= militia->getProductionPrice()) {
			if (map.getUnitInd(positionX, positionY) % 10 == 0) {
				this->production -= militia->getProductionPrice();
				militia->setPlayerID(this->playerID);
				militia->spawn(positionX, positionY, map);
				actor.push_back(*militia);
			}
			else
				std::cout << "<error> no space under the town;\n";
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << militia->getProductionPrice() << ")\n";
		break;
	case 3:
		if (this->production >= legion->getProductionPrice()) {
			if (map.getUnitInd(positionX, positionY) % 10 == 0) {
				this->production -= legion->getProductionPrice();
				legion->setPlayerID(this->playerID);
				legion->spawn(positionX, positionY, map);
				actor.push_back(*legion);
			}
			else
				std::cout << "<error> no space under the town;\n";
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << legion->getProductionPrice() << ")\n";
		break;
	case 4:
		if (this->production >= cavalry->getProductionPrice()) {
			if (map.getUnitInd(positionX, positionY) % 10 == 0) {
				this->production -= cavalry->getProductionPrice();
				cavalry->setPlayerID(this->playerID);
				cavalry->spawn(positionX, positionY, map);
				actor.push_back(*cavalry);
			}
			else
				std::cout << "<error> no space under the town;\n";
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << cavalry->getProductionPrice() << ")\n";
		break;
	case 5:
		if (this->production >= chariot->getProductionPrice()) {
			if (map.getUnitInd(positionX, positionY) % 10 == 0) {
				this->production -= chariot->getProductionPrice();
				chariot->setPlayerID(this->playerID);
				chariot->spawn(positionX, positionY, map);
				actor.push_back(*chariot);
			}
			else
				std::cout << "<error> no space under the town;\n";
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << chariot->getProductionPrice() << ")\n";
		break;
	}
}
//1-Aqueduct, 2-Barracks, 3-Walls, 4-Lib, 5-Market
void Town::createBuilding(int building) {
	Aqueduct* aqueduct = new Aqueduct();			//1
	Barracks* barracks = new Barracks();			//2
	CityWalls* cityWalls = new CityWalls();			//3
	Library* library = new Library();				//4
	Marketplace* marketplace = new Marketplace();	//5

	switch (building) {
	case 1:
		if (this->production >= aqueduct->getProductionPrice()) {		//PRICE
			if (!static_cast<bool>(std::count_if(buildings.begin(), buildings.end(), [](Building& index) {return index.getName() == "Aqueduct"; }))) {		//HAVE OR NOT
				this->production -= aqueduct->getProductionPrice();
				this->buildings.push_back(*aqueduct);
				this->population_limit += aqueduct->getIncraiseLimit();
				this->health += aqueduct->getIncreaseHP();
				std::cout << "\nAqueduct builded.";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
			}
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << aqueduct->getProductionPrice() << ")\n";
		break;
	case 2:
		if (this->production >= barracks->getProductionPrice()) {		//PRICE
			if (!static_cast<bool>(std::count_if(buildings.begin(), buildings.end(), [](Building& index) {return index.getName() == "Barracks"; }))) {		 //HAVE OR NOT
				this->production -= barracks->getProductionPrice();
				this->buildings.push_back(*barracks);
				this->population_limit += barracks->getIncraiseLimit();
				this->health += barracks->getIncreaseHP();
				std::cout << "\nBarracks builded.";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
			}
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << barracks->getProductionPrice() << ")\n";
		break;
	case 3:
		if (this->production >= cityWalls->getProductionPrice()) {		//PRICE
			if (!static_cast<bool>(std::count_if(buildings.begin(), buildings.end(), [](Building& index) {return index.getName() == "City Walls"; }))) {	//HAVE OR NOT
				this->production -= cityWalls->getProductionPrice();
				this->buildings.push_back(*cityWalls);
				this->population_limit += cityWalls->getIncraiseLimit();
				this->health += cityWalls->getIncreaseHP();
				std::cout << "\nCity Walls builded.";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
			}
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << cityWalls->getProductionPrice() << ")\n";
		break;
	case 4:
		if (this->production >= library->getProductionPrice()) {		//PRICE
			if (!static_cast<bool>(std::count_if(buildings.begin(), buildings.end(), [](Building& index) {return index.getName() == "Library"; }))) { 		//HAVE OR NOT
				this->production -= library->getProductionPrice();
				this->buildings.push_back(*library);
				this->population_limit += library->getIncraiseLimit();
				this->health += library->getIncreaseHP();
				std::cout << "\nLibrary builded.";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
			}
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << library->getProductionPrice() << ")\n";
		break;
	case 5:
		if (this->production >= marketplace->getProductionPrice()) {	//PRICE
			if (!static_cast<bool>(std::count_if(buildings.begin(), buildings.end(), [](Building& index) {return index.getName() == "Marketplace"; }))) {	//HAVE OR NOT
				this->production -= marketplace->getProductionPrice();
				this->buildings.push_back(*marketplace);
				this->population_limit += marketplace->getIncraiseLimit();
				this->health += marketplace->getIncreaseHP();
				std::cout << "\nMarketplace builded.";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
			}
		}
		else
			std::cout << "<error> no resourses: prod(" << this->production << "/" << marketplace->getProductionPrice() << ")\n";
		break;
	}
}
void Town::setColorByID() {
	if (this->playerID == 1)
		townSprite.setColor(sf::Color(180, 180, 255));//blue
	else if (this->playerID == 2)
		townSprite.setColor(sf::Color(255, 180, 180));//red
	else if (this->playerID == 3)
		townSprite.setColor(sf::Color(255, 255, 100));//yellow
	else if (this->playerID == 4)
		townSprite.setColor(sf::Color(180, 255, 180));//green
	else if (this->playerID == 5)
		townSprite.setColor(sf::Color(100, 255, 255));//purple
	else if (this->playerID == 6)
		townSprite.setColor(sf::Color(220, 125, 220));//pink
	else if (this->playerID > 6)
		townSprite.setColor(sf::Color(50, 50, 50));//dark
}
#pragma region GETERS
//GETERS
int Town::getHealth() {
	return this->health;
}
int Town::getProduction() {
	return this->production;
}
int Town::getGoldIncome() {
	return this->goldIncome;
}
int Town::getFood() {
	return this->food;
}
int Town::getTrade() {
	return this->trade;
}
int Town::getPopulation() {
	return this->population;
}
int Town::getPopulation_limit() {
	return this->population_limit;
}
int Town::getHappines() {
	return this->happines;
}
int Town::getPlayer_id() {
	return this->playerID;
}
int Town::getScience() {
	return this->science;
}
int Town::getDamage() {
	return this->damage;
}
std::string Town::getName() {
	return this->name;
}
int Town::getPositionX() {
	return this->positionX;
}
int Town::getPositionY() {
	return this->positionY;
}
#pragma endregion
#pragma region SETERS
//SETTERS
void Town::setPosition(int x, int y) {
	this->positionX = x;
	this->positionY = y;
	this->townSprite.setPosition(this->positionX, this->positionY);
	this->populationText.setPosition(this->positionX + 10, this->positionY);
}
void Town::setHealth(int health) {
	this->health = health;
}
void Town::setProduction(int prod) {
	this->production = production;
}
void Town::setgoldIncome(int goldIncome) {
	this->goldIncome = goldIncome;
}
void Town::setFood(int food) {
	this->food = food;
}
void Town::setTrade(int trade) {
	this->trade = trade;
}
void Town::setPopulation(int population) {
	this->population = population;
}
void Town::setHappines(int happines) {
	this->happines = happines;
}
void Town::setPlayer_id(int player_id) {
	this->playerID = player_id;
}
void Town::setPopulation_limit(int population_limit) {
	this->population_limit = population_limit;
}
void Town::setScience(int science) {
	this->science = science;
}
void Town::setName(std::string name) {
	this->name = name;
}
void Town::setDamage(int damage) {
	this->damage = damage;
}
#pragma endregion
//OTHER
bool isMouseInWindow(sf::RenderWindow& w) { return (sf::Mouse::getPosition(w).x >= 0 && sf::Mouse::getPosition(w).x < w.getSize().x) && ((sf::Mouse::getPosition(w).y >= 0 && sf::Mouse::getPosition(w).y < w.getSize().y)) ? true : false; }
void Town::statInfo(sf::RenderWindow& w) {
	sf::Texture menuTexture;
	menuTexture.loadFromFile("Icons\\VerticalScroll.png");
	sf::Sprite menuSprite(menuTexture);
	menuSprite.setPosition(this->townSprite.getPosition().x + 32, this->townSprite.getPosition().y);
	menuSprite.setScale(sf::Vector2f(4, 4));

	sf::Font font;
	font.loadFromFile("18536.ttf");
	sf::Text tProdaction, tHealth, tFood, tPopulationLimit, tPopulation, tHappines;
	//inicializate----------------------------------
	tProdaction.setFont(font);
	std::string productionstr = "Production = ";
	productionstr += std::to_string(this->production);
	tProdaction.setString(productionstr);
	tProdaction.setFillColor(sf::Color::Black);
	tProdaction.setCharacterSize(14);
	tProdaction.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32);

	tHealth.setFont(font);
	std::string healthstr = "Health = ";
	healthstr += std::to_string(this->health);
	tHealth.setString(healthstr);
	tHealth.setFillColor(sf::Color::Black);
	tHealth.setCharacterSize(14);
	tHealth.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32 + 23 * 1);

	tFood.setFont(font);
	std::string Foodstr = "Food = ";
	Foodstr += std::to_string(this->food);
	tFood.setString(Foodstr);
	tFood.setFillColor(sf::Color::Black);
	tFood.setCharacterSize(14);
	tFood.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32 + 23 * 2);

	tPopulation.setFont(font);
	std::string poppstr = "Population = ";
	poppstr += std::to_string(this->population);
	tPopulation.setString(poppstr);
	tPopulation.setFillColor(sf::Color::Black);
	tPopulation.setCharacterSize(14);
	tPopulation.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32 + 23 * 3);

	tPopulationLimit.setFont(font);
	std::string popstr = "Population\nLimit = ";
	popstr += std::to_string(this->population);
	tPopulationLimit.setString(popstr);
	tPopulationLimit.setFillColor(sf::Color::Black);
	tPopulationLimit.setCharacterSize(14);
	tPopulationLimit.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32 + 23 * 4);

	tHappines.setFont(font);
	std::string hepstr = "Happines = ";
	hepstr += std::to_string(this->happines);
	tHappines.setString(hepstr);
	tHappines.setFillColor(sf::Color::Black);
	tHappines.setCharacterSize(14);
	tHappines.setPosition(this->townSprite.getPosition().x + 32 + 40, this->townSprite.getPosition().y + 32 + 23 * 6);

	w.draw(menuSprite);
	w.draw(tProdaction);
	w.draw(tHealth);
	w.draw(tFood);
	w.draw(tPopulation);
	w.draw(tPopulationLimit);
	w.draw(tHappines);
}
void Town::draw(sf::RenderWindow& w, Map& map) {
	if (!map.isFog(positionX, positionY)) {
		std::string prod;
		prod = std::to_string(this->population);
		this->populationText.setString(prod);
		w.draw(this->townSprite);
		w.draw(this->populationText);
		if (this->isMenu)
			statInfo(w);
	}
}
void Town::endOfTurn(Map& map, int& gold, int& science) {
	//map.getTile(this->positionX, this->positionY).getName();
	int buildingTotalGoldIncome = 0;
	for (auto i : buildings) {
		buildingTotalGoldIncome += i.getgoldPerTurn();
	}
	gold += buildingTotalGoldIncome + population;
	int buildingTotalScienceIncome = 0;
	for (auto i : buildings) {
		buildingTotalScienceIncome += i.getScienceMultiplier();
	}
	science += buildingTotalScienceIncome;

	this->happines += gold + this->food + this->population_limit;
	if (this->food > 30 && this->happines > 1000 && this->population < population_limit) {
		this->population++;
		this->food = 0;
		this->happines = 0;
	}

	this->food += map.getTile(this->positionX, this->positionY).getFood();
	this->production += map.getTile(this->positionX, this->positionY).getProdaction();
	this->trade += map.getTile(this->positionX, this->positionY).getTrade();

	if (population > 9) {
		if (populationText.getPosition().x == this->positionX + 10)
			populationText.setPosition(populationText.getPosition().x - 7, populationText.getPosition().y);
	}
	if (population < 10) {
		if (populationText.getPosition().x == this->positionX + 3)
			populationText.setPosition(populationText.getPosition().x + 7, populationText.getPosition().y);
	}
}
std::string Town::getSaveTownInfo() {
	std::string unitInfo;
	unitInfo += this->name;
	unitInfo += " ";
	unitInfo += std::to_string(this->playerID);
	unitInfo += " ";
	unitInfo += std::to_string(this->positionX);
	unitInfo += " ";
	unitInfo += std::to_string(this->positionY);
	unitInfo += " ";
	unitInfo += std::to_string(this->health);
	unitInfo += " ";
	unitInfo += std::to_string(this->damage);
	unitInfo += " ";
	unitInfo += std::to_string(this->population);
	unitInfo += " ";
	unitInfo += std::to_string(this->population_limit);
	unitInfo += " ";
	unitInfo += std::to_string(this->production);
	unitInfo += " ";
	unitInfo += std::to_string(this->food);
	unitInfo += " ";
	unitInfo += std::to_string(this->trade);
	unitInfo += " ";
	unitInfo += std::to_string(this->happines);
	unitInfo += " ";
	unitInfo += std::to_string(this->goldIncome);
	unitInfo += " ";
	unitInfo += std::to_string(this->science);
	unitInfo += "\n~\n";
	for (auto i : buildings) {
		unitInfo += i.getName();
		unitInfo += "%";
	}

	return unitInfo;
}
void Town::spawn(int x, int y, Map& map) {
	setPosition(x, y);
	map.pushUnit(x, y, this->playerID * 100 + 50);
	setColorByID();
}