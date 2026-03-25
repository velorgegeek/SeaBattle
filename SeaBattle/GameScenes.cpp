#include "GameScenes.h"
#include "Scene.h"
#include <vector>
#include "constants.h"
PrepareScene::PrepareScene(Game* game) : Scene(game)  {
    //0 - index SquareField
    sf::RectangleShape* rectangle2 = new sf::RectangleShape{ sf::Vector2f(sizeSquare,sizeSquare) };

    rectangle2->setFillColor(sf::Color::Blue);
    rectangle2->setOutlineThickness(1);
    rectangle2->setOutlineColor(sf::Color::Black);
    

    sf::RectangleShape* readyButton = new sf::RectangleShape{ sf::Vector2f(sizeSquare * 2,sizeSquare) };

    readyButton->setFillColor(sf::Color::Blue);
    readyButton->setOutlineThickness(1);
    readyButton->setOutlineColor(sf::Color::Black);
    readyButton->setPosition(sf::Vector2f(520, 520));

    drawableObj.push_back(rectangle2);
    drawableObj.push_back(readyButton);
}
void PrepareScene::draw(sf::RenderWindow& window) {
    auto rectangle = dynamic_cast<sf::RectangleShape*>(drawableObj[0]);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            switch (game->playerField[i][j]._status) {
            case Cell::status::none:
                rectangle->setFillColor(sf::Color::Yellow);
                break;
            case Cell::status::blocked:
                rectangle->setFillColor(sf::Color::Green);
                break;
            }
            if (game->playerField[i][j].boat != nullptr) {
                rectangle->setFillColor(sf::Color::Red);
            }
            rectangle->setPosition(sf::Vector2f(sizeSquare * i + offsetX, sizeSquare * j + offsetY));
            window.draw(*rectangle);
        }
    }
    for (auto i : game->getBoats()) {
        window.draw(i->sprite);
    }
    if (drawReadyButton) {
        auto readyButton = dynamic_cast<sf::RectangleShape*>(drawableObj[1]);
        window.draw(*readyButton);
    }

}
void PrepareScene::eventHandler(const sf::Event* event, const sf::RenderWindow& window) {
    if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (MousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            if (!playerReady) {
                for (auto i : game->manager.getBoats()) {
                    if (i->sprite.getGlobalBounds().contains(worldPos)) {
                        dragboat.dragBoat(i);
                        if (!dragboat.boat->cordinMap.empty()) {
                            setBoatToMap(dragboat.boat->cordinMap, nullptr);
                            setBlocked(dragboat.boat->cordinMap, Game::blockedCell::remove);
                        }
                        break;
                    }
                }
            }
            else {
                if (drawReadyButton) {
                    auto readyButton = dynamic_cast<sf::RectangleShape*>(drawableObj[1]);
                    if (readyButton->getGlobalBounds().contains(worldPos)) {
                        playerReady = !playerReady
                    }
                }
            }
        }
    }
    else if (const auto* KeyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (timeRotate >= rotateTime) {
            timeRotate = 0;
            if (KeyPressed->scancode == sf::Keyboard::Scancode::V) {
                if (dragboat.boat != nullptr) {
                    dragboat.changeOrientation();
                }
                else {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    for (auto i : manager.getBoats()) {
                        if (i->sprite.getGlobalBounds().contains(worldPos)) {
                            changeOrientation(i);
                        }
                    }
                }
            }
        }
    }
    else if (const auto* MouseMoved = event->getIf<sf::Event::MouseMoved>()) {
        if (game->dragboat.drag) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            dragboat.boat->setPos(sf::Vector2f{ worldPos.x, worldPos.y });
        }
    }
    else if (const auto* MouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (dragboat.drag) {
            setPos();
        }
    }
}