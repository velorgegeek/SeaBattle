#pragma once


#include "SFML/Graphics.hpp"
#include <vector>
class Game;

class Scene {
protected:
	Game* game;
	std::vector<sf::RectangleShape*> drawableObj;
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void eventHandler(const sf::Event* event, const sf::RenderWindow& window) = 0;
	Scene(Game* game) : game(game) {};
	virtual ~Scene() = default;
};

class PrepareScene : public Scene {

	bool playerReady = 0;
	bool drawReadyButton = 0;

public:
	PrepareScene(Game* game);
	void draw(sf::RenderWindow& window) override;
	void eventHandler(const sf::Event* event, const sf::RenderWindow& window) override;

};

class FightScene : public Scene {

public:
	FightScene(Game* game);
	void draw(sf::RenderWindow& window) override;
	void eventHandler(const sf::Event* event, const sf::RenderWindow& window) override;

};