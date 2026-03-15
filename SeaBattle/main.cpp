
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
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(52, 50+5);
    sf::RectangleShape rectangle2{ sf::Vector2f(sizeSquare,sizeSquare) };
    rectangle2.setFillColor(sf::Color::Blue);
    rectangle.setOrigin(rectangle.getSize().x/2, rectangle.getSize().y/2);
    rectangle2.setOutlineThickness(1);
    rectangle2.setOutlineColor(sf::Color::Black);
    sf::Clock clock;

    while(window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        game.updateTimerRotate(time);
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
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                switch (game.enemyField[i][j]) {
                case 0:
                    rectangle2.setFillColor(sf::Color::Yellow);
                    break;
                case 1:
                    rectangle2.setFillColor(sf::Color(255, 0, 0));
                    break;
                case 2:
                    rectangle2.setFillColor(sf::Color::Blue);
                    break;
                case 3:
                    rectangle2.setFillColor(sf::Color::Black);
                    break;
                }
                rectangle2.setPosition(sizeSquare * i + offsetEnemyX, sizeSquare * j + offsetEnemyY);
                window.draw(rectangle2);
                }
            }
        
        
        for (auto boat : game.getBoats()) {
           window.draw(boat->sprite);
        }

        window.display();
    }
}


