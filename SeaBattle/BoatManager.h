#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Boat;
class BoatManager{
	sf::Texture textureBoats;
	std::vector<Boat*> boats;
	int countDead;
public:
	BoatManager();
	void getHit(Boat* boat);
	void setSprite(const Boat* boat);
	std::vector<Boat*> getBoats() const { return boats; }
	void initBoat();
};