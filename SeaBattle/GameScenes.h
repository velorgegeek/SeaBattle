#pragma once
#include "Scene.h"
#include "Game.h"
class PrepareScene : Scene {

	PrepareScene(Game* game) : Scene(game) {};

	bool playerReady = 0;
	bool drawReadyButton = 0;

	void draw(sf::RenderWindow& window) override;
	void eventHandler(const sf::Event* event, const sf::RenderWindow& window) override;

};