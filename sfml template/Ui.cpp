#include "Ui.h"

Ui::Ui() {
	sf::Texture* tex = new sf::Texture;
	tex->loadFromFile("Icons\\VerticalScroll.png");
	vScrollSprite.setTexture(*tex);
	this->font.loadFromFile("18536.ttf");
	this->tgold.setFont(this->font);
	this->tsience.setFont(this->font);
	this->tturn.setFont(this->font);
	this->tyear.setFont(this->font);

	this->tgold.setFillColor(sf::Color(0, 0, 0));
	this->tsience.setFillColor(sf::Color(0, 0, 0));
	this->tturn.setFillColor(sf::Color(0, 0, 0));
	this->tyear.setFillColor(sf::Color(0, 0, 0));

	sf::Text log;
	for (int i = 0; i < LOGS_COUNT; i++) {
		this->gLog.push_back(log);
		this->gLog[i].setFont(this->font);
		this->gLog[i].setFillColor(sf::Color(255, 255, 255));
		this->gLog[i].setString("");
		//this->gLog[i].setScale(0.7, 0.7);
	}
}

void Ui::gameLog(sf::RenderWindow& w) {}

void Ui::resize(sf::RenderWindow& w) {
	vScrollSprite.setScale(sf::Vector2f(static_cast<float>(w.getSize().x) / 300, static_cast<float>(w.getSize().x) / 300));
	this->vScrollSprite.setPosition(static_cast<float>(w.getView().getCenter().x - w.getSize().x / 2), static_cast<float>(w.getView().getCenter().y + w.getSize().y / 2 - 57 * vScrollSprite.getScale().y));

	this->tgold.setCharacterSize(static_cast<float>(w.getSize().x) / 60);
	this->tgold.setPosition(vScrollSprite.getPosition().x + 10 * vScrollSprite.getScale().x, vScrollSprite.getPosition().y + 10 * vScrollSprite.getScale().y);

	this->tsience.setCharacterSize(static_cast<float>(w.getSize().x) / 60);
	this->tsience.setPosition(vScrollSprite.getPosition().x + 10 * vScrollSprite.getScale().x, vScrollSprite.getPosition().y + 20 * vScrollSprite.getScale().y);

	this->tturn.setCharacterSize(static_cast<float>(w.getSize().x) / 60);
	this->tturn.setPosition(vScrollSprite.getPosition().x + 10 * vScrollSprite.getScale().x, vScrollSprite.getPosition().y + 30 * vScrollSprite.getScale().y);

	this->tyear.setCharacterSize(static_cast<float>(w.getSize().x) / 60);
	this->tyear.setPosition(vScrollSprite.getPosition().x + 10 * vScrollSprite.getScale().x, vScrollSprite.getPosition().y + 40 * vScrollSprite.getScale().y);
}

void Ui::setParams(int gold, int sience, int turn, int year) {
	std::string tmp;
	tmp = "Gold: ";
	tmp += std::to_string(gold);
	this->tgold.setString(tmp);

	tmp = "Sci.: ";
	tmp += std::to_string(sience);
	this->tsience.setString(tmp);

	tmp = "Turn: ";
	tmp += std::to_string(turn);
	this->tturn.setString(tmp);

	tmp = "Year: ";
	tmp += std::to_string(year);
	this->tyear.setString(tmp);
}

void Ui::setStringLogs(std::string text, bool doesClear) {
	if (!doesClear) {
		if (currentLog < LOGS_COUNT) {
			this->gLog.at(currentLog).setString(text);
			currentLog++;
		}
		else
			this->currentLog = 0;
	}
	else {
		for (int i = 0; i < LOGS_COUNT; i++) {
			this->gLog[i].setString(" ");
		}
		this->gLog[0].setString(text);
		currentLog = 0;
	}
}

void Ui::draw(sf::RenderWindow& w) {
	w.draw(this->vScrollSprite);
	w.draw(this->tgold);
	w.draw(this->tsience);
	w.draw(this->tturn);
	w.draw(this->tyear);

	for (int i = 0; i < LOGS_COUNT; i++) {
		//Move all other logs
		if (i != 0)
			this->gLog[i].setPosition(gLog[i - 1].getPosition().x, gLog[i - 1].getPosition().y + this->gLog[i].getCharacterSize());
		else
			//move first log
			this->gLog[i].setPosition(w.getView().getCenter().x - w.getSize().x / 2, w.getView().getCenter().y - w.getSize().y / 2);

		//change size
		this->gLog[i].setCharacterSize(static_cast<float>(w.getSize().x) / 60);

		//if player doesn't use log-hide it
		if (isLog)
			w.draw(this->gLog[i]);
	}
}