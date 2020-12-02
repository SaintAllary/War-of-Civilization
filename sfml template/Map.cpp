#include "Map.h"
#define _FOG 1000
#define _TERRAIN 100
#define _RESOURCE 10

void baseNoise4(int val, int sizex, int sizey, std::vector<std::vector<int>>& arr) {
	std::vector<std::vector<int>>arr1;	//[x][y]
	for (int x = 0; x < sizex; x++) {
		std::vector<int>arr_t;
		for (int y = 0; y < sizey; y++) {
			arr_t.push_back(rand() % 3);
		}
		arr1.push_back(arr_t);
	}
	for (int x = 1; x < sizex - 1; x++) {
		for (int y = 1; y < sizey - 1; y++) {
			arr1[x][y] = (arr1[x + 1][y] + arr1[x - 1][y] + arr1[x][y + 1] + arr1[x][y - 1]) / 4 /*+ (arr1[x + 1][y + 1] + arr1[x - 1][y - 1] + arr1[x - 1][y + 1] + arr1[x + 1][y - 1]) / 4*/;
		}
	}
	for (int x = 1; x < sizex - 1; x++) {
		for (int y = 1; y < sizey - 1; y++) {
			if (arr1[x][y] >= 1)arr[x][y] = val;
		}
	}
}
void baseNoise8(int val, int sizex, int sizey, std::vector<std::vector<int>>& arr) {
	std::vector<std::vector<int>>arr1;	//[x][y]
	for (int x = 0; x < sizex; x++) {
		std::vector<int>arr_t;
		for (int y = 0; y < sizey; y++) {
			arr_t.push_back(rand() % 3);
		}
		arr1.push_back(arr_t);
	}
	for (int x = 1; x < sizex - 1; x++) {
		for (int y = 1; y < sizey - 1; y++) {
			arr1[x][y] = (arr1[x + 1][y] + arr1[x - 1][y] + arr1[x][y + 1] + arr1[x][y - 1] + arr1[x + 1][y + 1] + arr1[x - 1][y - 1] + arr1[x - 1][y + 1] + arr1[x + 1][y - 1]) / 7;
		}
	}
	for (int x = 1; x < sizex - 1; x++) {
		for (int y = 1; y < sizey - 1; y++) {
			if (arr1[x][y] >= 1)arr[x][y] = val;
		}
	}
}

Map::Map(int sizeX, int sizeY, int resGenChanse) {
	//1-hill  2-forest  3-grass  4-mountain
	for (int i = 0; i < sizeX; i++) {
		std::vector<int>unitstmp;
		for (int j = 0; j < sizeY; j++) {
			unitstmp.push_back(0);
		}
		this->units.push_back(unitstmp);
	}

	for (int x = 0; x < sizeX; x++) {
		std::vector<int>arr_t;
		for (int y = 0; y < sizeY; y++) {
			arr_t.push_back(3);
		}
		map.push_back(arr_t);
	}
	//NOISE GENERATION
	//1-hill  2-forest  3-grass  4-mountain 5-Ocean 6-Plain
	baseNoise4(4, sizeX, sizeY, map);
	baseNoise4(1, sizeX, sizeY, map);
	baseNoise4(2, sizeX, sizeY, map);
	baseNoise4(3, sizeX, sizeY, map);
	baseNoise8(6, sizeX, sizeY, map);
	baseNoise8(5, sizeX, sizeY, map);
	baseNoise4(1, sizeX, sizeY, map);
	baseNoise4(2, sizeX, sizeY, map);
	for (int x = 0; x < sizeX; x++) {
		map[x][0] = 5;
		map[x][map[x].size() - 1] = 5;
	}
	for (int y = 0; y < sizeY; y++) {
		map[0][y] = 5;
		map[map.size() - 1][y] = 5;
	}
	//Terrains normalize
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			map[x][y] *= 100;
		}
	}
	//FOG
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			map[x][y] += _FOG;
		}
	}

	//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (!(rand() % resGenChanse)) {
				if (map.at(i).at(j) % _FOG == 100) {			//HILL
					if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 1;//COAL GEN
					else if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 6;//OIL GEN
				}
				else if (map.at(i).at(j) % _FOG == 200) {		//FOREST
					if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 2;//GAME GEN
				}
				else if (map.at(i).at(j) % _FOG == 300) {		//GRASS
					if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 1;//COAL GEN
					else if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 4;//HORSES GEN
				}
				else if (map.at(i).at(j) % _FOG == 400) {		//MOUNTAIN
					if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 3;//GOLD GEN
					else if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 5;//OASIS GEN
				}
				else if (map.at(i).at(j) % _FOG == 600) {		//FOREST
					if (rand() % resGenChanse == 1)
						map.at(i).at(j) += 2;//GAME GEN
				}
			}
		}
	}
}

void Map::saveMap() {
	std::string path = PATH_TO_SAVE_1;
	std::ofstream fout;
	fout.open(path, std::ofstream::app);
	if (!fout.is_open())
		std::cout << "Error, file wasn't opened" << std::endl;
	else {
		for (auto i : map) {
			for (auto j : i) {
				fout << j << " ";
			}
			fout << "\n";
		}
		fout << "=\n";
		for (auto i : units) {
			for (auto j : i) {
				fout << j << " ";
			}
			fout << "\n";
		}
		fout << "=\n";
		std::cout << "Successes save\n ";
	}

	fout.close();
}

void Map::loadTerrains(std::string line) {
	//  line  =  103 100 200 505
	std::vector<int> INTbuf;
	std::vector<std::vector<int>> newmap;
	while (line.size() > 3) {
		INTbuf.push_back(std::stoi(line));
		if (INTbuf.at(INTbuf.size() - 1) >= 1000)
			line.erase(0, 5);
		else
			line.erase(0, 4);
	}
	//std::cout << "\n\n\n\n";
	int size = INTbuf.size() / map.size();

	for (int i = 0, o = 0; i < size; i++) {
		std::vector<int> newmap1buf;
		for (int j = 0; j < size; j++, o++) {
			newmap1buf.push_back(INTbuf.at(o));
		}
		newmap.push_back(newmap1buf);
	}

	map = newmap;
}
void Map::loadUnits(std::string line) {
	//  line  =  0 100 0 251
	std::vector<int> INTbuf;
	std::vector<std::vector<int>> newmap;
	while (line.size() > 1) {
		INTbuf.push_back(std::stoi(line));
		if (INTbuf.at(INTbuf.size() - 1) == 0)
			line.erase(0, 2);
		else
			line.erase(0, 4);
	}
	int size = INTbuf.size() / units.size();

	for (int i = 0, o = 0; i < size; i++) {
		std::vector<int> newmap1buf;
		for (int j = 0; j < size; j++, o++) {
			newmap1buf.push_back(INTbuf.at(o));
		}
		newmap.push_back(newmap1buf);
	}

	units = newmap;
}

Terrain Map::getTile(int x, int y) {
	x /= 32;
	y /= 32;
	return getTileVec(x, y);
}
Terrain Map::getTileVec(int x, int y) {
	if (map.at(x).at(y) % _FOG / 100 == 1) {				//HILL DRAW
		if (map.at(x).at(y) % 100 == 1) {		//COAL DRAW
			return Hills(1);
		}
		else if (map.at(x).at(y) % 100 == 6) {	//OIL DRAW
			return Hills(2);
		}
		return Hills();
	}
	else if (map.at(x).at(y) % _FOG / 100 == 2) {			//FOREST DRAW
		if (map.at(x).at(y) % 100 == 2) {		//GAME DRAW
			return Forest(1);
		}
		return Forest();
	}
	else if (map.at(x).at(y) % _FOG / 100 == 3) {			//GRASSLAND DRAW
		if (map.at(x).at(y) % 100 == 4) {		//HORSES DRAW
			return Grassland(2);
		}
		else if (map.at(x).at(y) % 100 == 1) {	//COAL DRAW
			return Grassland(1);
		}
		return Grassland();
	}
	else if (map.at(x).at(y) % _FOG / 100 == 4) {			//MOUNTAIN DRAW
		if (map.at(x).at(y) % 100 == 3) {		//GOLD DRAW
			return Mountain(1);
		}
		else if (map.at(x).at(y) % 100 == 5) {	//OASIS DRAW
			return Mountain(2);
		}
		return Mountain();
	}
	else if (map.at(x).at(y) % _FOG / 100 == 5)				//OCEAN
		return Ocean();
	else if (map.at(x).at(y) % _FOG / 100 == 6) {			//PLAINS DRAW
		if (map.at(x).at(y) % 100 == 2) {		//HORSES DRAW
			return Plains(1);
		}
		return Plains();
	}
}
int Map::getUnitInd(int x, int y) {
	x /= 32;
	y /= 32;
	if (x >= 0 && x < static_cast<int>(units.size())) {
		if (y >= 0 && y < static_cast<int>(units.size())) {
			return this->units.at(x).at(y);
		}
		else return 0;
	}
	else return 0;
}
int Map::getUnitID(int x, int y) {
	return getUnitInd(x, y) % 100;
}
bool Map::isTown(int x, int y) {
	return getUnitInd(x, y) % _FOG / 100 % 10;
}
bool Map::isFog(int x, int y) {
	x /= 32;
	y /= 32;
	return map[x][y] / _FOG;
}
int Map::getUnitPlayerID(int x, int y) {
	return getUnitInd(x, y) % _FOG / 100;
}
void Map::pushUnit(int x, int y, int unit) {
	x /= 32;
	y /= 32;
	if (x > 0 && x < static_cast<int>(units.size())) {
		if (y > 0 && y < static_cast<int>(units.size())) {
			if (this->units.at(x).at(y) % 100 / 10 == 5)
				this->units.at(x).at(y) += unit % 10;
			else this->units.at(x).at(y) = unit;
		}
	}
}
void Map::moveUnit(int x, int y, int newx, int newy, int unitPlayerID) {
	x /= 32;
	y /= 32;
	newx /= 32;
	newy /= 32;
	if (newx > 0 && newx < static_cast<int>(units.size())) {
		if (newy > 0 && newy < static_cast<int>(units.size())) {
			if (this->units.at(x).at(y) % 100 / 10 == 5) {//FIX THIS
				this->units.at(newx).at(newy) = this->units.at(x).at(y) - 50;
				this->units.at(x).at(y) -= (this->units.at(x).at(y) % 10);
			}
			else {
				this->units.at(newx).at(newy) = this->units.at(x).at(y);
				this->units.at(x).at(y) = 0;

				if (unitPlayerID == 1)
					radarFog(newx, newy);
			}
		}
	}
}

void Map::radarFog(int newx, int newy) {
	if (map.at(newx).at(newy) / _FOG)
		this->map.at(newx).at(newy) -= 1000;

	if (map.at(newx - 1).at(newy - 1) / _FOG)
		this->map.at(newx - 1).at(newy - 1) -= 1000;

	if (map.at(newx + 1).at(newy - 1) / _FOG)
		this->map.at(newx + 1).at(newy - 1) -= 1000;

	if (map.at(newx - 1).at(newy + 1) / _FOG)
		this->map.at(newx - 1).at(newy + 1) -= 1000;

	if (map.at(newx + 1).at(newy + 1) / _FOG)
		this->map.at(newx + 1).at(newy + 1) -= 1000;

	if (map.at(newx + 1).at(newy) / _FOG)
		this->map.at(newx + 1).at(newy) -= 1000;

	if (map.at(newx - 1).at(newy) / _FOG)
		this->map.at(newx - 1).at(newy) -= 1000;

	if (map.at(newx).at(newy - 1) / _FOG)
		this->map.at(newx).at(newy - 1) -= 1000;

	if (map.at(newx).at(newy + 1) / _FOG)
		this->map.at(newx).at(newy + 1) -= 1000;
}

void Map::delUnit(int x, int y) {
	x /= 32;
	y /= 32;
	if (this->units.at(x).at(y) % 100 / 10 == 5)
		units.at(x).at(y) -= (units.at(x).at(y) % 10);
	else
		this->units.at(x).at(y) = 0;
}
std::vector<std::vector<int>>& Map::_getVecTerrainsInt() { return this->map; }
std::vector<std::vector<int>>& Map::_getVecUnitsInt() { return this->units; }
void Map::__getInfo_DEBUG(int x, int y) {
	if (x / 32 >= 0 && x / 32 < static_cast<int>(units.size())) {
		if (y / 32 >= 0 && y / 32 < static_cast<int>(units.size())) {
			getTile(x, y).__getInfo_DEBUG();
			std::cout << "unut_index = " << this->units[x / 32][y / 32];
			std::cout << "\n-map-tile-end-\n";
		}
	}
}
void Map::getInfo(int x, int y, sf::RenderWindow& w) {
	if (x / 32 >= 0 && x / 32 < static_cast<int>(units.size())) {
		if (y / 32 >= 0 && y / 32 < static_cast<int>(units.size())) {
			getTile(x, y).getInfo(w);
		}
	}
}

void Map::reTakeTown(int x, int y, int newPlayerID) {
	x /= 32;
	y /= 32;
	int tmp = units.at(x).at(y) % 100;
	tmp += (newPlayerID * 100);
	units.at(x).at(y) = tmp;
}
void Map::draw(sf::RenderWindow& w) {
	Hills hill;
	Forest forest;
	Grassland grass;
	Mountain mountain;
	Ocean ocean;
	Plains plains;

	Coal coal;
	Game game;
	Gold gold;
	Horses horses;
	Oasis oasis;
	Oil oil;

	//1-hill  2-forest  3-grass  4-mountain 5-ocean 6-plains
	for (int i = 0; i < static_cast<int>(map.size()); i++) {
		for (int j = 0; j < static_cast<int>(map.at(i).size()); j++) {
			if (map[i][j] / _FOG) {}
			else {
				if (map[i][j] % _FOG / 100 == 1) {					//HILL DRAW
					hill.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					hill.draw(w);
					//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
					if (map[i][j] % _FOG % 100 == 1) {			//COAL DRAW
						coal.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						coal.draw(w);
					}
					else if (map[i][j] % _FOG % 100 == 6) {	//OIL DRAW
						oil.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						oil.draw(w);
					}
				}
				else if (map[i][j] % _FOG / 100 == 2) {			//FOREST DRAW
					forest.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					forest.draw(w);
					//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
					if (map[i][j] % _FOG % 100 == 2) {			//GAME DRAW
						game.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						game.draw(w);
					}
				}
				else if (map[i][j] % _FOG / 100 == 3) {			//GRASSLAND DRAW
					grass.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					grass.draw(w);
					//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
					if (map[i][j] % _FOG % 100 == 4) {			//HORSES DRAW
						horses.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						horses.draw(w);
					}
					else if (map[i][j] % _FOG % 100 == 1) {	//COAL DRAW
						coal.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						coal.draw(w);
					}
				}
				else if (map[i][j] % _FOG / 100 == 4) {			//MOUNTAIN DRAW
					mountain.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					mountain.draw(w);
					//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
					if (map[i][j] % _FOG % 100 == 3) {			//GOLD DRAW
						gold.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						gold.draw(w);
					}
					else if (map[i][j] % _FOG % 100 == 5) {	//OASIS DRAW
						oasis.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						oasis.draw(w);
					}
				}
				else if (map[i][j] % _FOG / 100 == 5) {			//OCEAN
					ocean.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					ocean.draw(w);
				}
				else if (map[i][j] % _FOG / 100 == 6) {			//PLAINS DRAW
					plains.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
					plains.draw(w);
					//1-Coal  2-Game  3-Gold  4-Horses  5-Oasis  6-Oil
					if (map[i][j] % _FOG % 100 == 2) {			//HORSES DRAW
						horses.setPosition(static_cast<float>(i * 32), static_cast<float>(j * 32));
						horses.draw(w);
					}
				}
			}
		}
	}
}