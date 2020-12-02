#pragma once
#include<SFML/Graphics.hpp>

#define LOGS_COUNT 8

class Ui {
private:
	//sf::RectangleShape DownLeftRect;
	//sf::RectangleShape DownRightRect;
	//sf::RectangleShape DownMiddleRect;
	sf::Font font;
	sf::Text tgold;
	sf::Text tsience;
	sf::Text tturn;
	sf::Text tyear;
	std::vector<sf::Text> gLog;
	sf::Sprite vScrollSprite;
public:
	bool isLog = false;
	int currentLog = 0;

	Ui();
	void gameLog(sf::RenderWindow& w);
	void resize(sf::RenderWindow& w);
	void draw(sf::RenderWindow& w);
	void setParams(int gold, int sience, int turn, int year);

	//for user
	void setStringLogs(std::string text, bool doesClear = false);
};
