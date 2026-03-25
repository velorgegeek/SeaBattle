#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
class Scene {
protected:
	Game* game;
	std::vector<sf::Drawable*> drawableObj;
public:
	virtual void draw(sf::RenderWindow& window);
	virtual void eventHandler(const sf::Event* event, const sf::RenderWindow& window);
	Scene(Game* game) : game(game) {};
};