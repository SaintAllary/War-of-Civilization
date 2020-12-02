#pragma once
#include "Actor.h"
#include "GameManager.h"

class WindowManager {
private:
	sf::RenderWindow w;
	bool isMenu = true;//true

public:
	WindowManager();
	//create new game if false or empty, load game if true
	void newGameWindow(bool doesLoad = false);
	//move camera
	void cameraControl(sf::View& view, sf::Window& window);
	//check is mouse in window coordination
	bool isMouseInWindow(sf::RenderWindow& w);
	//function to get pos mouse in window
	int getPosMouseByWindowX(sf::RenderWindow& w);
	//function to get pos mouse in window
	int getPosMouseByWindowY(sf::RenderWindow& w);
	//main menu function has a few buttons
	void mainMenu(sf::RenderWindow& w);
	//game menu function has a few buttons but is a little bit another
	void gameMenu(sf::RenderWindow& w, GameManager& game);

	sf::RenderWindow& getWindow();
};