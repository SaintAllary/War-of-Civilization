#pragma once
#include <SFML/Graphics.hpp>
#include "path.h"

class Resourses {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	void draw(sf::RenderWindow& w);
	virtual void setPosition(float x, float y) { sprite.setPosition(x, y); }
};