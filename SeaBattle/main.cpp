
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "BoatManager.h"
#include "Boat.h"
#include "cell.h"
#include "Game.h"
#include "DragBoat.h"

int main()
{  

    Game game = Game();
    sf::RectangleShape hitbox;
    hitbox.setFillColor(sf::Color::Blue);
    sf::RectangleShape rectangle{sf::Vector2f(sizeBoat,sizeBoat*3)};
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(52, 50+5);
    sf::RectangleShape rectangle2{ sf::Vector2f(sizeSquare,sizeSquare) };
    rectangle2.setFillColor(sf::Color::Blue);
    rectangle.setOrigin(rectangle.getSize().x/2, rectangle.getSize().y/2);
    rectangle2.setOutlineThickness(1);
    rectangle2.setOutlineColor(sf::Color::Black);
    
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            game.eventHandler(event, window);
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                switch (game.playerField[i][j]._status) {
                case Cell::status::none:
                    rectangle2.setFillColor(sf::Color::Yellow);
                    break;
                case Cell::status::blocked:
                    rectangle2.setFillColor(sf::Color::Green);
                    break;
                }
                if (game.playerField[i][j].boat != nullptr) {
                    rectangle2.setFillColor(sf::Color::Red);
                }
                rectangle2.setPosition(sizeSquare * i + offsetX, sizeSquare * j + offsetY);
                window.draw(rectangle2);
            }
        }
        
        
        for (auto boat : game.getBoats()) {
           window.draw(boat->sprite);
        }

        window.display();
    }
}


