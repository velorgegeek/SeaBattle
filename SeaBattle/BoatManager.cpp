#include "BoatManager.h"
#include "Boat.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
void BoatManager::setSprite(const Boat* boat) {
	//boat->
}
void BoatManager::getHit(Boat* boat) {
	if (boat->getHit()) {
		countDead++;
	};
}
BoatManager::BoatManager() {
	textureBoats.loadFromFile("boats.png");
	initBoat();
}
void BoatManager::initBoat() {
	boats.clear();
	sf::Sprite sprite(textureBoats);

	boats.push_back(new Boat(Boat::orientationBoat::Horizontal,textureBoats, 4));
	std::cout << "4-х палубник добавлен";
	for (int i = 0; i < 2; i++) {
		boats.push_back(new Boat(Boat::orientationBoat::Horizontal, textureBoats, 3));
		std::cout << "3-х палубник добавлен";
	}
	for (int i = 0; i < 3; i++) {

		boats.push_back(new Boat(Boat::orientationBoat::Horizontal, textureBoats,2));
		std::cout << "2-х палубник добавлен";
	}
	for (int i = 0; i < 4; i++) {
		boats.push_back(new Boat(Boat::orientationBoat::Horizontal, textureBoats, 1));
		std::cout << "1 палубник добавлен";
	}

}