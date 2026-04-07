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
    sf::RenderWindow window(sf::VideoMode({ 1000,  800}), "SFML works!");

    sf::Clock clock;

    while(window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        game.updateTimerRotate(time);
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            game.eventHandler(&*event, window);
        }

        window.clear(sf::Color::White);

        game.draw(window);
        window.display();
    }
}


