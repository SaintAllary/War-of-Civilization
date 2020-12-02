#pragma once
#include"AI.h"
#include"Map.h"
#include"Ui.h"

class GameManager {
private:
	Ui ui;
	std::vector<Actor> actors;
	Map map;
	int currentYear;
public:
	sf::Sprite ref;
	bool isRef;

	GameManager();

	Map& getMap();
	std::vector<Actor>& getActors();

	void setYear(int year);//set current year
	int& getYear();//return current year
	void draw(sf::RenderWindow& w, sf::View& v);
	Actor& findActorHidden(int ID); // find and return vector by ID
	Actor& findActor(int mouse_x, int mouse_y);//get mouse position and return vector of units of actor
	void saveGame();
	void loadGame();
	void deleteAllActors();
	Ui& getUi();
};
