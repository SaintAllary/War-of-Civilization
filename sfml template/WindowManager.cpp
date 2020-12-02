#include "WindowManager.h"

WindowManager::WindowManager() {
	this->w.create(sf::VideoMode(1000, 600), "WC" /*,sf::Style::Fullscreen*/);
	this->w.setFramerateLimit(60);
}

void WindowManager::newGameWindow(bool doesLoad) {
	try {
		GameManager game;

		if (doesLoad)
			game.loadGame();

		sf::View view(w.getView());

		while (w.isOpen()) {
			sf::Event event;

			while (w.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape)
						isMenu = !isMenu;
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::F1)
						game.getUi().isLog = !(game.getUi().isLog);
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Tab)
						game.isRef = !game.isRef;
				}

				//CLOSE--------------
				if (event.type == event.Closed)
					w.close();
				if (event.type == sf::Event::Resized)
					view.setSize(sf::Vector2f(event.size.width, event.size.height));

				if (!isMenu) {
					if (!(game.getActors().at(0).didLose())) {
						//Check is mouse in window
						if (isMouseInWindow(w)) {
							//all other control
							if (game.getActors().at(0).takeControl(event, game.getMap(), w, game.getYear())) {
								for (int i = 1; i < game.getActors().size(); i++)
									game.getActors().at(i).endOfTurnBot(game.getMap(), game.getActors().at(0));
							}
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//If you want to attack or move unit
							{
								if (event.MouseButtonReleased)
									game.getActors().at(0).takeControlUnit(event, game.getMap(), w, game.findActor(getPosMouseByWindowX(w), getPosMouseByWindowY(w)));
							}
						}
					}
					else
						game.getUi().setStringLogs("ALL YOUR UNITS ARE DEAD, TOWNS BURNED ,YOU LOST");
				}
			}
			//CAMERA CONTROL

			if (isMouseInWindow(w) && !game.isRef)
				cameraControl(view, w);

			w.setView(view);
			//WINDOW-FILL-COLOR
			w.clear(sf::Color::Black);
			//draw all in game
			game.draw(w, view);

			if (isMenu)
				gameMenu(w, game);

			//DISPLAY
			w.display();
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

void WindowManager::gameMenu(sf::RenderWindow& w, GameManager& game) {
	sf::Texture menuTexture1;
	menuTexture1.loadFromFile("Icons\\menu.png");
	sf::Sprite bContinue(menuTexture1), bSaveGame(menuTexture1), bExit(menuTexture1), bLoadGame(menuTexture1);
	sf::Font font;
	font.loadFromFile("18536.ttf");
	sf::Text tContinue, tSaveGame, tExit, tLoadGame;

	//inicializate----------------------------------
	tContinue.setFont(font);
	tContinue.setString("Continue");
	tSaveGame.setFont(font);
	tSaveGame.setString("Save game");
	tLoadGame.setFont(font);
	tLoadGame.setString("Load game");
	tExit.setFont(font);
	tExit.setString("Exit");

	bContinue.setScale(1.5, 1.5);
	bSaveGame.setScale(1.5, 1.5);
	bLoadGame.setScale(1.5, 1.5);
	bExit.setScale(1.5, 1.5);
	//BOUNDS-----------------------------------------------
	sf::FloatRect localBounds = tContinue.getLocalBounds();
	tContinue.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tContinue.getLocalBounds();
	tSaveGame.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tLoadGame.getLocalBounds();
	tLoadGame.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tExit.getLocalBounds();
	tExit.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	//BAR---------------------------------------POS
	bContinue.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bContinue.getScale().x), static_cast<float>(w.getView().getCenter().y - 45 * bContinue.getScale().y));
	bSaveGame.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bSaveGame.getScale().x), static_cast<float>(w.getView().getCenter().y - 15 * bSaveGame.getScale().x));
	bLoadGame.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bLoadGame.getScale().x), static_cast<float>(w.getView().getCenter().y + 15 * bLoadGame.getScale().x));
	bExit.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bExit.getScale().x), static_cast<float>(w.getView().getCenter().y + 45 * bExit.getScale().x));

	//TEXT-----------------------------------------POS
	tContinue.setPosition(static_cast<float>(bContinue.getPosition().x + 100 * bContinue.getScale().x), static_cast<float>(bContinue.getPosition().y + 15));
	tSaveGame.setPosition(static_cast<float>(bSaveGame.getPosition().x + 100 * bSaveGame.getScale().x), static_cast<float>(bSaveGame.getPosition().y + 15));
	tLoadGame.setPosition(static_cast<float>(bLoadGame.getPosition().x + 100 * bLoadGame.getScale().x), static_cast<float>(bLoadGame.getPosition().y + 15));
	tExit.setPosition(static_cast<float>(bExit.getPosition().x + 100 * bExit.getScale().x), static_cast<float>(bExit.getPosition().y + 15));

	while (isMenu) {
		sf::Event ev;
		while (w.pollEvent(ev)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				isMenu = false;
			if (ev.type == sf::Event::Closed)
				w.close();
			if (isMouseInWindow(w)) {
				//all other control
				if ((sf::IntRect(sf::FloatRect(bContinue.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bContinue.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bContinue.getGlobalBounds().width, bContinue.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
					bContinue.setColor(sf::Color(150, 150, 150));
				else
					bContinue.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(sf::FloatRect(bSaveGame.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bSaveGame.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bSaveGame.getGlobalBounds().width, bSaveGame.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
					bSaveGame.setColor(sf::Color(150, 150, 150));
				else
					bSaveGame.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(sf::FloatRect(bLoadGame.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bLoadGame.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bLoadGame.getGlobalBounds().width, bLoadGame.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
					bLoadGame.setColor(sf::Color(150, 150, 150));
				else
					bLoadGame.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(sf::FloatRect(bExit.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bExit.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bExit.getGlobalBounds().width, bExit.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
					bExit.setColor(sf::Color(150, 150, 150));
				else
					bExit.setColor(sf::Color(255, 255, 255));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//If you want to attack or move unit
				{
					if (ev.MouseButtonReleased) {
						if ((sf::IntRect(sf::FloatRect(bExit.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bExit.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bExit.getGlobalBounds().width, bExit.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
							w.close();
						if ((sf::IntRect(sf::FloatRect(bContinue.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bContinue.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bContinue.getGlobalBounds().width, bContinue.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
							isMenu = false;
						if ((sf::IntRect(sf::FloatRect(bSaveGame.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bSaveGame.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bSaveGame.getGlobalBounds().width, bSaveGame.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
							game.saveGame();
						if ((sf::IntRect(sf::FloatRect(bLoadGame.getGlobalBounds().left - w.getView().getCenter().x + w.getSize().x / 2, bLoadGame.getGlobalBounds().top - w.getView().getCenter().y + w.getSize().y / 2, bLoadGame.getGlobalBounds().width, bLoadGame.getGlobalBounds().height)).contains(sf::Mouse::getPosition(w))))
							game.loadGame();
					}
				}
			}
		}

		//bar
		w.draw(bContinue);
		w.draw(bSaveGame);
		w.draw(bLoadGame);
		w.draw(bExit);
		//text
		w.draw(tContinue);
		w.draw(tSaveGame);
		w.draw(tLoadGame);
		w.draw(tExit);

		w.display();
	}
}

void WindowManager::cameraControl(sf::View& view, sf::Window& w) {
	if (sf::Mouse::getPosition(w).x >= w.getSize().x - BORDER_PIXEL_32)
		view.move(BORDER_PIXEL_32 / 6, 0);
	if (sf::Mouse::getPosition(w).x <= BORDER_PIXEL_32)
		view.move(-BORDER_PIXEL_32 / 6, 0);
	if (sf::Mouse::getPosition(w).y <= BORDER_PIXEL_32)
		view.move(0, -BORDER_PIXEL_32 / 6);
	if (sf::Mouse::getPosition(w).y >= w.getSize().y - BORDER_PIXEL_32)
		view.move(0, BORDER_PIXEL_32 / 6);
}

bool WindowManager::isMouseInWindow(sf::RenderWindow& w) {
	return (sf::Mouse::getPosition(w).x >= 0 && sf::Mouse::getPosition(w).x < w.getSize().x) && ((sf::Mouse::getPosition(w).y >= 0 && sf::Mouse::getPosition(w).y < w.getSize().y)) ? true : false;
}

int WindowManager::getPosMouseByWindowX(sf::RenderWindow& w) {
	return sf::Mouse::getPosition(w).x + (w.getView().getCenter().x - w.getSize().x / 2);
}

int WindowManager::getPosMouseByWindowY(sf::RenderWindow& w) {
	return  sf::Mouse::getPosition(w).y + (w.getView().getCenter().y - w.getSize().y / 2);
}

void WindowManager::mainMenu(sf::RenderWindow& w) {
	sf::Texture texture;
	texture.loadFromFile("Icons\\menuBG.png");
	texture.setSmooth(1);
	sf::Sprite backGroundImage(texture);

	backGroundImage.scale(3, 3);
	backGroundImage.setPosition(w.getView().getCenter().x - w.getSize().x / 2, w.getView().getCenter().y - w.getSize().y / 2);

	sf::Texture menuTexture1;
	menuTexture1.loadFromFile("Icons\\menu.png");
	sf::Sprite bNewGame(menuTexture1), bContinue(menuTexture1), bExit(menuTexture1), bLoadGame(menuTexture1);
	sf::Font font;
	font.loadFromFile("18536.ttf");
	sf::Text tNewGame, tContinue, tExit, tLoadGame;

	//inicializate----------------------------------
	tNewGame.setFont(font);
	tNewGame.setString("New game");
	tContinue.setFont(font);
	tContinue.setString("Continue");
	tLoadGame.setFont(font);
	tLoadGame.setString("Load game");
	tExit.setFont(font);
	tExit.setString("Exit");

	bNewGame.setScale(1.5, 1.5);
	bContinue.setScale(1.5, 1.5);
	bLoadGame.setScale(1.5, 1.5);
	bExit.setScale(1.5, 1.5);
	//BOUNDS-----------------------------------------------
	sf::FloatRect localBounds = tNewGame.getLocalBounds();
	tNewGame.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tNewGame.getLocalBounds();
	tContinue.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tLoadGame.getLocalBounds();
	tLoadGame.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	localBounds = tExit.getLocalBounds();
	tExit.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	//BAR---------------------------------------POS
	bNewGame.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bNewGame.getScale().x), static_cast<float>(w.getView().getCenter().y - 45 * bNewGame.getScale().y));
	bContinue.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bContinue.getScale().x), static_cast<float>(w.getView().getCenter().y - 15 * bContinue.getScale().x));
	bLoadGame.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bLoadGame.getScale().x), static_cast<float>(w.getView().getCenter().y + 15 * bLoadGame.getScale().x));
	bExit.setPosition(static_cast<float>(w.getView().getCenter().x - 100 * bExit.getScale().x), static_cast<float>(w.getView().getCenter().y + 45 * bExit.getScale().x));

	//TEXT-----------------------------------------POS
	tNewGame.setPosition(static_cast<float>(bNewGame.getPosition().x + 100 * bNewGame.getScale().x), static_cast<float>(bNewGame.getPosition().y + 15));
	tContinue.setPosition(static_cast<float>(bContinue.getPosition().x + 100 * bContinue.getScale().x), static_cast<float>(bContinue.getPosition().y + 15));
	tLoadGame.setPosition(static_cast<float>(bLoadGame.getPosition().x + 100 * bLoadGame.getScale().x), static_cast<float>(bLoadGame.getPosition().y + 15));
	tExit.setPosition(static_cast<float>(bExit.getPosition().x + 100 * bExit.getScale().x), static_cast<float>(bExit.getPosition().y + 15));

	while (isMenu) {
		sf::Event ev;
		while (w.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				w.close();
			if (isMouseInWindow(w)) {
				//all other control
				if ((sf::IntRect(bNewGame.getGlobalBounds()).contains(sf::Mouse::getPosition(w))))
					bNewGame.setColor(sf::Color(150, 150, 150));
				else
					bNewGame.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(bContinue.getGlobalBounds()).contains(sf::Mouse::getPosition(w))))
					bContinue.setColor(sf::Color(150, 150, 150));
				else
					bContinue.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(bLoadGame.getGlobalBounds()).contains(sf::Mouse::getPosition(w))))
					bLoadGame.setColor(sf::Color(150, 150, 150));
				else
					bLoadGame.setColor(sf::Color(255, 255, 255));
				if ((sf::IntRect(bExit.getGlobalBounds()).contains(sf::Mouse::getPosition(w))))
					bExit.setColor(sf::Color(150, 150, 150));
				else
					bExit.setColor(sf::Color(255, 255, 255));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//If you want to attack or move unit
				{
					if (ev.MouseButtonReleased) {
						if ((sf::IntRect(bNewGame.getGlobalBounds()).contains(sf::Mouse::getPosition(w)))) {
							isMenu = false;
							newGameWindow();
						}
						if ((sf::IntRect(bContinue.getGlobalBounds()).contains(sf::Mouse::getPosition(w)))) {
							isMenu = false;
							newGameWindow(true);
						}

						if ((sf::IntRect(bExit.getGlobalBounds()).contains(sf::Mouse::getPosition(w))))
							w.close();
						if ((sf::IntRect(bLoadGame.getGlobalBounds()).contains(sf::Mouse::getPosition(w)))) {
							isMenu = false;
							newGameWindow(true);
						}
					}
				}
			}
		}
		w.clear(sf::Color(0, 0, 0));

		w.draw(backGroundImage);
		//bar
		w.draw(bNewGame);
		w.draw(bContinue);
		w.draw(bLoadGame);
		w.draw(bExit);
		//text
		w.draw(tNewGame);
		w.draw(tContinue);
		w.draw(tLoadGame);
		w.draw(tExit);

		w.display();
	}
}

sf::RenderWindow& WindowManager::getWindow() {
	return this->w;
}