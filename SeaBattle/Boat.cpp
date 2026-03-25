#include "Boat.h"
#include "constants.h"

#include <iostream>
Boat::Boat(const Boat::orientationBoat& orientation, const sf::Texture& texture, int count) : sprite(texture){

	countDeck = count;
	orient = orientation;
	if (orient == Boat::orientationBoat::Horizontal) {
		rectangle.setSize(sf::Vector2f(sizeBoat * count, sizeBoat));
		rect = sf::FloatRect(sf::Vector2f(600, 600), sf::Vector2f(sizeSquare * count, sizeSquare));
	}
	else {
		rectangle.setSize(sf::Vector2f(sizeBoat, sizeBoat * count));
		rect = sf::FloatRect(sf::Vector2f(600, 600), sf::Vector2f(sizeSquare, sizeSquare * count));
	}
	sf::Vector2f center(rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f);
	rectangle.setOrigin({ rectangle.getSize().x / 2, rectangle.getSize().y / 2 });
	rectangle.setPosition(center);
	rectangle.setFillColor(sf::Color::Black);
	sprite.setTexture(texture);
	int row = count - 1;               
	sprite.setTextureRect(sf::IntRect({ 0, row * 32 },{ 32 + 24 * count - 1, 32}));
	int size = sizeBoat * count;
	double x = size / 32;
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f });
	sprite.setPosition(center);
}
void Boat::setPos(const sf::Vector2f& v2) {
	rect.position.x = v2.x;
	rect.position.y = v2.y;
	

	sf::Vector2f center(rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f);
	sprite.setPosition(center);
}
void Boat::setPos(const sf::FloatRect& v2) {
	rect = v2;
	sf::Vector2f center(rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f);
	std::cout << "position.x: " << v2.position.x << " " << "position.y" << v2.position.y<<std::endl;
	sprite.setPosition(center);
}
bool Boat::getHit() {
	diedDeck++;
	return (diedDeck == countDeck) ? true : false;
}
void Boat::changeOrientation() {
	if (orient == Boat::orientationBoat::Vertical) {
		orient = Boat::orientationBoat::Horizontal;
		sprite.rotate(sf::degrees(90.f));
		rect = sf::FloatRect(rect.position, sf::Vector2f(sizeSquare * countDeck, sizeSquare));
	}
	else {
		orient = Boat::orientationBoat::Vertical;
		sprite.rotate(sf::degrees(-90.f));

		rect = sf::FloatRect(rect.position, sf::Vector2f(sizeSquare, sizeSquare * countDeck));
	}
	sf::Vector2f center(rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f);
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f });
	sprite.setPosition(center);
	/*rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	rectangle.setPosition(center);*/
}