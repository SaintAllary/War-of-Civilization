#include "GameManager.h"

GameManager::GameManager() {
	Actor* player = new Actor("player");
	player->setPlayerID(1);
	Settlers* firstS = new Settlers;
	firstS->setPlayerID(player->getPlayerID());
	firstS->spawn(/*(1 + rand() % map._getVecTerrainsInt().size() - 2) * 32*/32 * 15, /*(1 + rand() % map._getVecTerrainsInt().at(0).size() - 2) * 32*/32 * 15, this->map);
	player->__PUSH_UNIT_DEBUG(firstS);

	//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
	AI* enemyActor = new AI(2);
	enemyActor->setPlayerID(2);
	////////////////////////////CREATING UNITS
	Legion* legionEnemy = new Legion;
	Militia* militiaEnemy = new Militia;
	militiaEnemy->setPlayerID(2);
	militiaEnemy->spawn(32 * 10, 32 * 9, map);
	//EnemyUnitVector.push_back(militiaEnemy);
	enemyActor->__PUSH_UNIT_DEBUG(militiaEnemy);
	legionEnemy->setPlayerID(2);
	legionEnemy->spawn(32 * 9, 32 * 10, map);
	//EnemyUnitVector.push_back(legionEnemy);
	enemyActor->__PUSH_UNIT_DEBUG(legionEnemy);
	Town* townEnemy = new Town;
	townEnemy->setPlayer_id(2);
	townEnemy->spawn(32 * 10, 32 * 10, this->map);
	enemyActor->__PUSH_TOWN_DEBUG(townEnemy);
	Town* townEnemy2 = new Town;
	townEnemy2->setPlayer_id(2);
	townEnemy2->spawn(32 * 7, 32 * 7, this->map);
	enemyActor->__PUSH_TOWN_DEBUG(townEnemy2);
	//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-

	AI* third = new AI(2);
	third->setPlayerID(3);
	Settlers* settlers3 = new Settlers;
	Legion* legionEnemy3 = new Legion;
	legionEnemy3->setPlayerID(3);
	legionEnemy3->spawn(32 * 20, 32 * 20, map);
	settlers3->setPlayerID(3);
	settlers3->spawn(32 * 19, 32 * 19, map);
	third->__PUSH_UNIT_DEBUG(settlers3);
	third->__PUSH_UNIT_DEBUG(legionEnemy3);

	this->actors.push_back(*player);
	this->actors.push_back(*enemyActor);
	this->actors.push_back(*third);

	this->currentYear = -4000;
	this->isRef = false;
	sf::Texture* refer = new sf::Texture;
	refer->loadFromFile(PATH_TO_ICON_REFERENCE);
	this->ref.setTexture(*refer);
}

Map& GameManager::getMap() {
	return this->map;
}

std::vector<Actor>& GameManager::getActors() {
	return this->actors;
}

void GameManager::setYear(int year) {
	this->currentYear = year;
}

int& GameManager::getYear() {
	return this->currentYear;
}

void GameManager::draw(sf::RenderWindow& w, sf::View& view) {
	map.draw(w);
	for (auto i : this->actors)
		i.draw(w, this->map);
	//if(IsMenu)
	ui.resize(w);
	ui.setParams(this->actors[0].getTotalGold(), this->actors[0].getTotalScience(), (this->currentYear + 4000) / 5, this->currentYear);
	this->ui.draw(w);

	ref.setScale(sf::Vector2f(static_cast<float>(w.getSize().x) / 1000, static_cast<float>(w.getSize().y) / 600));

	ref.setPosition(static_cast<float>(w.getView().getCenter().x - w.getSize().x / 2), static_cast<float>(w.getView().getCenter().y + w.getSize().y / 2 - 600 * ref.getScale().y));
	if (isRef)
		w.draw(ref);
}

Actor& GameManager::findActorHidden(int ID) {
	if (ID < 100 && ID > 0) {
		if (this->actors.at(ID - 1).getPlayerID() == ID)
			return this->actors.at(ID - 1);
	}
	else return this->actors.at(0);
}

Actor& GameManager::findActor(int mouse_x, int mouse_y) {
	if ((map.getUnitInd(mouse_x, mouse_y)) / 100 != 0 && (map.getUnitInd(mouse_x, mouse_y)) / 100 != this->actors.at(0).getPlayerID()) //check index of unit
		return findActorHidden((map.getUnitInd(mouse_x, mouse_y)) / 100);
}

void GameManager::saveGame() {
	remove(PATH_TO_SAVE_1);
	map.saveMap();
	for (auto i : actors)
		i.saveTotalnfo();
	this->ui.setStringLogs("Game successfully saved");
}

#pragma region UNitsMap_LOAD
//find digit from heap
std::string getUnitInfoFromFile(int actorInd) {
	std::string line;
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	short isnext = 0;
	short actori = 0;
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (isnext == 2) {
				fin >> buffer;
				if (buffer == "#")
					actorInd--;

				if (actorInd == 0 && buffer == "#")
					break;

				line += buffer;
				line += " ";

				if (buffer == "&")
					line.clear();
			}
			else {
				fin >> buffer;
				if (buffer == "=")
					isnext++;
			}
		}
		//std::cout << line << std::endl;//==============================DEBUG
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();
	return line;
}

int getUnitsCount(int actorInd) {
	std::string buffer = getUnitInfoFromFile(actorInd);
	short counter = 0;
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] == '|')
			counter++;
	}
	return counter;
}

std::string sliseStrings(std::string str, int index) {
	std::string tmp;
	index--;
	//1 0 1 3 0 0 1 3 160 160 |1 1 3 3 0 0 3 3 192 192 |
	for (auto i : str) {
		if (i == '|' && index == 0)
			break;
		if (index != 0) {
			if (i == '|') {
				index--;
				tmp.clear();
			}
		}
		if (i != '|')
			tmp += i;

		//std::cout << tmp << std::endl;
	}
	if (index == 0) {
		return tmp;
	}
}

int getIntFromStringByIndex(std::string com, int index) {
	int tmp = 0;
	std::string time;
	if (index == 1) {
		for (int i = 0; i < com.size(); i++) {
			if (!std::isdigit(com[i]))
				break;
			time += com[i];
		}
		return stoi(time);
	}
	for (int i = 1; i < com.size(); i++) {
		if ((std::isdigit(com[i]) || com[i] == '|') && (com[i - 1] == ' ')) {
			index--;
		}
		if (index == 1) {
			time += com[i];
		}
		if (index == 0) {
			return stoi(time);
		}
	}
}

std::vector<Unit> getUnitVectorByActorInd(int actorInd) {
	//std::cout << "\n\nplayerID: " << actorInd;//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
	std::vector<Unit> tmp;
	//1 0 1 1 0 0 2 2 128 128 |1 1 3 3 0 0 3 2 96 96 |
	std::string preSlisedStr = getUnitInfoFromFile(actorInd);
	//std::cout << "\npreSlisedStr: " << preSlisedStr;//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
	for (int i = 0; i < getUnitsCount(actorInd); i++) {
		std::string slisedStr = sliseStrings(preSlisedStr, i + 1);
		//std::cout << "\nslisedStr: " << slisedStr;//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		int tmpUnitIndex = getIntFromStringByIndex(slisedStr, 7);
		//std::cout << "\nuID: " << tmpUnitIndex;//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		if (tmpUnitIndex == 1) {
			Settlers* settlers = new Settlers;
			settlers->setHealth(getIntFromStringByIndex(slisedStr, 1));
			settlers->setArmor(getIntFromStringByIndex(slisedStr, 2));
			settlers->setDamage(getIntFromStringByIndex(slisedStr, 3));
			settlers->setSteps(getIntFromStringByIndex(slisedStr, 4));
			settlers->setRank(getIntFromStringByIndex(slisedStr, 5));
			settlers->setCountOfKill(getIntFromStringByIndex(slisedStr, 6));
			settlers->setPlayerID(getIntFromStringByIndex(slisedStr, 8));
			settlers->setPosition(getIntFromStringByIndex(slisedStr, 9), getIntFromStringByIndex(slisedStr, 10));
			settlers->setColorByID();
			tmp.push_back(*settlers);
			//std::cout << "\nPushed s";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		}
		if (tmpUnitIndex == 2) {
			Militia* militia = new Militia();
			militia->setHealth(getIntFromStringByIndex(slisedStr, 1));
			militia->setArmor(getIntFromStringByIndex(slisedStr, 2));
			militia->setDamage(getIntFromStringByIndex(slisedStr, 3));
			militia->setSteps(getIntFromStringByIndex(slisedStr, 4));
			militia->setRank(getIntFromStringByIndex(slisedStr, 5));
			militia->setCountOfKill(getIntFromStringByIndex(slisedStr, 6));
			militia->setPlayerID(getIntFromStringByIndex(slisedStr, 8));
			militia->setPosition(getIntFromStringByIndex(slisedStr, 9), getIntFromStringByIndex(slisedStr, 10));
			militia->setColorByID();
			tmp.push_back(*militia);
			//std::cout << "\nPushed m";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		}
		if (tmpUnitIndex == 3) {
			Legion* legion = new Legion();
			legion->setHealth(getIntFromStringByIndex(slisedStr, 1));
			legion->setArmor(getIntFromStringByIndex(slisedStr, 2));
			legion->setDamage(getIntFromStringByIndex(slisedStr, 3));
			legion->setSteps(getIntFromStringByIndex(slisedStr, 4));
			legion->setRank(getIntFromStringByIndex(slisedStr, 5));
			legion->setCountOfKill(getIntFromStringByIndex(slisedStr, 6));
			legion->setPlayerID(getIntFromStringByIndex(slisedStr, 8));
			legion->setPosition(getIntFromStringByIndex(slisedStr, 9), getIntFromStringByIndex(slisedStr, 10));
			legion->setColorByID();
			tmp.push_back(*legion);
			//std::cout << "\nPushed l";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		}
		if (tmpUnitIndex == 4) {
			Cavalry* cavalry = new Cavalry();
			cavalry->setHealth(getIntFromStringByIndex(slisedStr, 1));
			cavalry->setArmor(getIntFromStringByIndex(slisedStr, 2));
			cavalry->setDamage(getIntFromStringByIndex(slisedStr, 3));
			cavalry->setSteps(getIntFromStringByIndex(slisedStr, 4));
			cavalry->setRank(getIntFromStringByIndex(slisedStr, 5));
			cavalry->setCountOfKill(getIntFromStringByIndex(slisedStr, 6));
			cavalry->setPlayerID(getIntFromStringByIndex(slisedStr, 8));
			cavalry->setPosition(getIntFromStringByIndex(slisedStr, 9), getIntFromStringByIndex(slisedStr, 10));
			cavalry->setColorByID();
			tmp.push_back(*cavalry);
			//std::cout << "\nPushed c";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		}
		if (tmpUnitIndex == 5) {
			Chariot* chariot = new Chariot();
			chariot->setHealth(getIntFromStringByIndex(slisedStr, 1));
			chariot->setArmor(getIntFromStringByIndex(slisedStr, 2));
			chariot->setDamage(getIntFromStringByIndex(slisedStr, 3));
			chariot->setSteps(getIntFromStringByIndex(slisedStr, 4));
			chariot->setRank(getIntFromStringByIndex(slisedStr, 5));
			chariot->setCountOfKill(getIntFromStringByIndex(slisedStr, 6));
			chariot->setPlayerID(getIntFromStringByIndex(slisedStr, 8));
			chariot->setPosition(getIntFromStringByIndex(slisedStr, 9), getIntFromStringByIndex(slisedStr, 10));
			chariot->setColorByID();
			tmp.push_back(*chariot);
			//std::cout << "\nPushed c";//DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-DEBUG-
		}
	}

	return tmp;
}

std::string getMapTerrainDataFromFile() {
	std::string line;
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> buffer;
			if (buffer == "=") {
				break;
			}
			line += buffer;
			line += " ";
		}
		//std::cout << "\n\n\n\n\n";
		//for (auto i : line)
		//{
		//	std::cout << i;
		//}
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();
	return line;
}

std::string getMapUnitDataFromFile() {
	std::string line;
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	bool isnext = false;
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (isnext) {
				fin >> buffer;
				if (buffer == "=") {
					break;
				}
				line += buffer;
				line += " ";
			}
			else {
				fin >> buffer;
				if (buffer == "=")
					isnext = true;
			}
		}
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();
	return line;
}
#pragma endregion

#pragma region actor_LOAD
std::string getActorInfoFromFile(int actorInd) {
	std::string line;
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	short isnext = 0;
	short actori = 0;
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (isnext == 2) {
				fin >> buffer;
				if (buffer == "_") {
					actorInd--;
				}
				if (actorInd == 0 && buffer == "_") {
					break;
				}

				line += buffer;
				line += " ";

				if (buffer == "#") {
					line.clear();
				}
			}
			else {
				fin >> buffer;
				if (buffer == "=")
					isnext++;
			}
		}
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();
	return line;
}

std::string getActorName(int actorInd) {
	std::string namebuf = getActorInfoFromFile(actorInd);
	for (int i = 0; i < namebuf.size(); i++) {
		if (!std::isalpha(namebuf.at(i)))
			namebuf.erase(i);
	}
	return namebuf;
}

int getActorTG(int actorInd) {
	std::string namebuf = getActorInfoFromFile(actorInd);
	std::string intbuf;
	for (int i = 0; i < namebuf.size(); i++) {
		if (std::isdigit(namebuf.at(i)) || (namebuf.at(i) == ' ')) { intbuf += namebuf[i]; }
	}
	intbuf.erase(0, 3);
	return stoi(intbuf);
}

int getActorTS(int actorInd) {
	std::string namebuf = getActorInfoFromFile(actorInd);
	std::string intbuf;
	for (int i = 0; i < namebuf.size(); i++) {
		if (std::isdigit(namebuf.at(i)) || (namebuf.at(i) == ' ')) { intbuf += namebuf[i]; }
	}
	intbuf.erase(0, 3);

	for (int j = 0; j < intbuf.size(); j++) {
		if (intbuf.at(j) == ' ') {
			intbuf.erase(0, j);
			break;
		}
	}

	return stoi(intbuf);
}

int getActorsCount() {
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	short isnext = 0;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> buffer;
			if (buffer == "_")
				isnext++;
		}
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();

	return isnext;
}
#pragma endregion

#pragma region TOWNS_LOAD
//return count of user's towns
int getTownsCount(int actorInd) {
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	short isnext = 0;

	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> buffer;

			if (actorInd == 0) {
				if (buffer == "~")
					isnext++;
			}
			if (buffer == "_" && actorInd == 0) {
				return isnext;
			}

			if (buffer == "_")
				actorInd--;
		}
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();

	return isnext;
}
//work perfectly
std::string getTownInfoFromFile(int actorInd) {
	std::string line;
	std::string buffer;
	std::string path = PATH_TO_SAVE_1;
	std::ifstream fin;
	fin.open(path);
	short isnext = 0;
	short _check = getTownsCount(actorInd);
	bool does_write = 1;
	int count_of_rep = getTownsCount(actorInd);

	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> buffer;

			if (_check == 0) {
				if (actorInd == 0 && buffer == "~") {
					return line;
				}
				if (actorInd == 0) {
					line += buffer;
					line += " ";
				}
				if (buffer == "_") {
					actorInd--;
				}
			}
			else {
				if (actorInd == 0 && buffer == "~" && count_of_rep > 0) {
					line += " |";
					does_write = 0;
					count_of_rep--;
				}
				if (actorInd == 0 && does_write) {
					line += buffer;
					line += " ";
				}
				if (actorInd == 0 && count_of_rep > 0) {
					if (buffer == "*") {
						does_write = true;
					}
				}
				if (count_of_rep == 0) {
					return line;
				}
				if (buffer == "_") {
					actorInd--;
				}
			}
		}
		//std::cout << line << std::endl;//==============================DEBUG
	}
	else
		std::cout << "Can't open file" << std::endl;
	fin.close();
	return line;
}
//WORK
std::string getStringFromSringByIndexTowns(std::string com) {
	int tmp = 0;
	std::string time;
	for (int i = 0; i < com.size(); i++) {
		if (!std::isdigit(com[i]) && !std::ispunct(com[i])) {
			time += com[i];
		}
		if (isdigit(com[i])) {
			break;
		}
	}
	return time;
}
//WORK
int getIntFromStringByIndexTowns(std::string com, int index) {
	int tmp = 0;
	std::string time;

	for (int i = 0; i < com.size(); i++) {
		if ((std::isdigit(com[i]) || com[i] == '|') && (com[i - 1] == ' ')) {
			index--;
		}
		if (index == 1) {
			time += com[i];
		}
	}
	return stoi(time);
}
#pragma endregion

std::vector<Town> getTownVectorByActorInd(int actorInd) {
	std::vector<Town> tmp;
	//1 0 1 1 0 0 2 2 128 128 |1 1 3 3 0 0 3 2 96 96 |
	std::string preSlisedStr = getTownInfoFromFile(actorInd);

	for (int i = 0; i < getTownsCount(actorInd); i++) {
		std::string slisedStr = sliseStrings(preSlisedStr, i + 1);
		Town* town = new Town;
		town->setPlayer_id(getIntFromStringByIndexTowns(slisedStr, 2));
		town->setPosition(getIntFromStringByIndexTowns(slisedStr, 3), getIntFromStringByIndexTowns(slisedStr, 4));
		town->setHealth(getIntFromStringByIndexTowns(slisedStr, 5));
		town->setDamage(getIntFromStringByIndexTowns(slisedStr, 6));
		town->setPopulation(getIntFromStringByIndexTowns(slisedStr, 7));
		town->setPopulation_limit(getIntFromStringByIndexTowns(slisedStr, 8));
		town->setProduction(getIntFromStringByIndexTowns(slisedStr, 9));
		town->setTrade(getIntFromStringByIndexTowns(slisedStr, 10));
		town->setHappines(getIntFromStringByIndexTowns(slisedStr, 11));
		town->setgoldIncome(getIntFromStringByIndexTowns(slisedStr, 12));
		town->setScience(getIntFromStringByIndexTowns(slisedStr, 13));
		town->setColorByID();

		tmp.push_back(*town);
	}

	return tmp;
}
//-------------------LOAD GAME
void GameManager::loadGame() {
	bool isEmpty = false;
	std::ifstream file;
	file.open(PATH_TO_SAVE_1);

	if (file) {
		map.loadUnits(getMapUnitDataFromFile());
		map.loadTerrains(getMapTerrainDataFromFile());
		if (this->actors.size() > 0) {
			this->deleteAllActors();
			//getActorInfoFromFile();
			for (int i = 1; i <= getActorsCount(); i++) {
				this->actors.push_back(Actor(getActorName(i), i));
				this->actors[i - 1].setTotalGold(getActorTG(i));
				this->actors[i - 1].setTotalScience(getActorTS(i));
				this->actors[i - 1].setUnitVector(getUnitVectorByActorInd(i));
				this->actors[i - 1].setUnitTown(getTownVectorByActorInd(i));
			}
		}
		else {
		}
		this->ui.setStringLogs("Successfully load", true);
	}
	else
		this->ui.setStringLogs("\nCant find this file : " PATH_TO_SAVE_1  " (game has started in NEW GAME order)");

	file.close();
}

void GameManager::deleteAllActors() {
	this->actors.clear();
}

Ui& GameManager::getUi() {
	return this->ui;
}