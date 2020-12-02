#include <iostream>
#include "Terrain.h";

Terrain::Terrain() {
	this->name = "<Terrain>";
	this->move = 0;
	this->food = 0;
	this->prodaction = 0;
	this->trade = 0;
	this->defense = 0;
}

sf::Texture Terrain::getTexture() {
	return this->texture;
}

std::string Terrain::getName() {
	return this->name;
}

int Terrain::getMove() {
	return this->move;
}

int Terrain::getFood() {
	return this->food;
}

int Terrain::getProdaction() {
	return this->prodaction;
}

int Terrain::getTrade() {
	return this->trade;
}

int Terrain::getDefense() {
	return this->defense;
}

bool Terrain::isWater() {
	return this->name == "ocean" ? true : false;
}

void Terrain::__getInfo_DEBUG() {
	std::cout << "\n-----tile-----\n";
	std::cout << "name = " << this->name << std::endl;
	std::cout << "move = " << this->move << std::endl;
	std::cout << "food = " << this->food << std::endl;
	std::cout << "prodaction = " << this->prodaction << std::endl;
	std::cout << "trade = " << this->trade << std::endl;
	std::cout << "defense = " << this->defense;
	std::cout << "\n---tile-end---\n";
}
void Terrain::getInfo(sf::RenderWindow& w) {
	sf::Texture menuTexture;
	menuTexture.loadFromFile("Icons\\VerticalScroll.png");
	sf::Sprite menuSprite(menuTexture);
	menuSprite.setPosition(this->sprite.getPosition().x - 184, this->sprite.getPosition().y - 228);
	menuSprite.setScale(sf::Vector2f(4, 4));

	sf::Font font;
	font.loadFromFile("18536.ttf");
	sf::Text tProdaction, tHealth, tFood, tPopulationLimit, tPopulation, tHappines;
	//inicializate----------------------------------
	tProdaction.setFont(font);
	std::string productionstr = "name = ";
	productionstr += this->name;
	tProdaction.setString(productionstr);
	tProdaction.setFillColor(sf::Color::Black);
	tProdaction.setCharacterSize(14);
	tProdaction.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228);

	tHealth.setFont(font);
	std::string healthstr = "move = ";
	healthstr += std::to_string(this->move);
	tHealth.setString(healthstr);
	tHealth.setFillColor(sf::Color::Black);
	tHealth.setCharacterSize(14);
	tHealth.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228 + 23 * 1);

	tFood.setFont(font);
	std::string Foodstr = "Food = ";
	Foodstr += std::to_string(this->food);
	tFood.setString(Foodstr);
	tFood.setFillColor(sf::Color::Black);
	tFood.setCharacterSize(14);
	tFood.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228 + 23 * 2);

	tPopulation.setFont(font);
	std::string poppstr = "prodaction = ";
	poppstr += std::to_string(this->prodaction);
	tPopulation.setString(poppstr);
	tPopulation.setFillColor(sf::Color::Black);
	tPopulation.setCharacterSize(14);
	tPopulation.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228 + 23 * 3);

	tPopulationLimit.setFont(font);
	std::string popstr = "trade = ";
	popstr += std::to_string(this->trade);
	tPopulationLimit.setString(popstr);
	tPopulationLimit.setFillColor(sf::Color::Black);
	tPopulationLimit.setCharacterSize(14);
	tPopulationLimit.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228 + 23 * 4);

	tHappines.setFont(font);
	std::string hepstr = "defense = ";
	hepstr += std::to_string(this->defense);
	tHappines.setString(hepstr);
	tHappines.setFillColor(sf::Color::Black);
	tHappines.setCharacterSize(14);
	tHappines.setPosition(this->sprite.getPosition().x - 184 + 40, this->sprite.getPosition().y - 228 + 23 * 6);

	w.draw(menuSprite);
	w.draw(tProdaction);
	w.draw(tHealth);
	w.draw(tFood);
	w.draw(tPopulation);
	w.draw(tPopulationLimit);
	w.draw(tHappines);
}

void Terrain::draw(sf::RenderWindow& w) {
	w.draw(sprite);
}