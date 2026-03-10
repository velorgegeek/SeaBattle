#pragma once
#include <SFML/Graphics.hpp>

class Boat {
public:
	enum class orientationBoat { Horizontal, Vertical };
	int countDeck;
	int diedDeck= 0;
	sf::Sprite sprite;
	orientationBoat orient;
	sf::RectangleShape rectangle;
	sf::FloatRect rect; 
	std::vector<std::pair<int, int>> cordinMap;
	void changeOrientation();
	bool getHit();
	void setPos(const sf::Vector2f& v2);
	void setPos(const sf::FloatRect& v2);
	Boat(const Boat::orientationBoat& orientation,const sf::Texture& texture,int count);
	Boat(const Boat::orientationBoat& orientation, int count);
};