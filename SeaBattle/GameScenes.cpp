#include "GameScenes.h"
#include <vector>
#include "Game.h"
#include "constants.h"
PrepareScene::PrepareScene(Game* game) : Scene(game)  {
    //0 - index SquareField
    sf::RectangleShape* rectangle2 = new sf::RectangleShape{ sf::Vector2f(constant::sizeSquare,constant::sizeSquare) };

    rectangle2->setFillColor(sf::Color::Blue);
    rectangle2->setOutlineThickness(1);
    rectangle2->setOutlineColor(sf::Color::Black);
    

    sf::RectangleShape* readyButton = new sf::RectangleShape{ sf::Vector2f(constant::sizeSquare * 3,constant::sizeSquare*2) };

    readyButton->setFillColor(sf::Color::Blue);
    readyButton->setOutlineThickness(1);
    readyButton->setOutlineColor(sf::Color::Black);
    readyButton->setPosition(sf::Vector2f(520, 520));

    drawableObj.push_back(rectangle2);
    drawableObj.push_back(readyButton);
}
void PrepareScene::draw(sf::RenderWindow& window) {
    auto rectangle = drawableObj[0];

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            switch (game->playerField[i][j]._status) {
            case Cell::status::none:
                rectangle->setFillColor(sf::Color::Yellow);
                break;
            case Cell::status::blocked:
                if (game->IsDraging()) {
                    rectangle->setFillColor(sf::Color::Green);
                }
                else {
                    rectangle->setFillColor(sf::Color::Yellow);
                }
                break;
            case Cell::status::hitted:
                rectangle->setFillColor(sf::Color::Cyan);
            }
            if (game->playerField[i][j].boat != nullptr) {
                rectangle->setFillColor(sf::Color::Red);
            }
            rectangle->setPosition(sf::Vector2f(constant::sizeSquare * i + constant::offsetX, constant::sizeSquare * j + constant::offsetY));
            window.draw(*rectangle);
        }
    }
    for (auto i : game->getBoats()) {
        window.draw(i->sprite);
    }
    if (drawReadyButton) {
        auto readyButton = (drawableObj[1]);
        window.draw(*readyButton);
    }

}
void PrepareScene::eventHandler(const sf::Event* event, const sf::RenderWindow& window) {
    if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (MousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            if (drawReadyButton) {
                auto readyButton = (drawableObj[1]);
                if (readyButton->getGlobalBounds().contains(worldPos)) {
                    playerReady = !playerReady;
                }
            }
            if (!playerReady) {
                for (auto i : game->getBoats()) {
                    if (i->sprite.getGlobalBounds().contains(worldPos)) {
                        game->drag(i);
                        drawReadyButton = 0;
                        break;
                    }
                }
            }
        }
    }
    else if (const auto* KeyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (playerReady) return;
        if (game->timeRotate >= constant::rotateTime) {
            game->timeRotate = 0;
            if (KeyPressed->scancode == sf::Keyboard::Scancode::V) {
                auto dragingBoat = game->getDragBoat();
                if (dragingBoat) {
                    dragingBoat->changeOrientation();
                }
                else {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    for (auto i : game->getBoats()) {
                        if (i->sprite.getGlobalBounds().contains(worldPos)) {
                            game->changeOrientationBoat(i);
                        }
                    }
                }
            }
        }
    }
    else if (const auto* MouseMoved = event->getIf<sf::Event::MouseMoved>()) {
        if (playerReady) return;
        auto dragingBoat = game->getDragBoat();
        if (dragingBoat) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            dragingBoat->setPos(sf::Vector2f{ worldPos.x, worldPos.y });
        }
    }
    else if (const auto* MouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (game->IsDraging()) {
            game->setPosBoat();
            if (game->getCountBoatOnMap() == 10) {
                drawReadyButton = 1;
            }
        }
    }
}

FightScene::FightScene(Game* game) : Scene(game) {
    sf::RectangleShape* rectangle2 = new sf::RectangleShape{ sf::Vector2f(constant::sizeSquare,constant::sizeSquare) };

    rectangle2->setFillColor(sf::Color::Blue);
    rectangle2->setOutlineThickness(1);
    rectangle2->setOutlineColor(sf::Color::Black);


    drawableObj.push_back(rectangle2);
}

void FightScene::draw(sf::RenderWindow& window) {
    auto rectangle = drawableObj[0];

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
            rectangle->setPosition(sf::Vector2f(constant::sizeSquare * i + constant::offsetX, constant::sizeSquare * j + constant::offsetY));
            window.draw(*rectangle);
        }
    }
    for (auto i : game->getBoats()) {
        window.draw(i->sprite);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            switch (game->enemyField[i][j]) {
            case 0:
                rectangle->setFillColor(sf::Color::Yellow);
                break;
            case 1:
                rectangle->setFillColor(sf::Color::Cyan);
                break;
            case 2:
                rectangle->setFillColor(sf::Color::Black);
            case 3: 
                rectangle->setFillColor(sf::Color::Red);
            }
            rectangle->setPosition(sf::Vector2f(constant::sizeSquare * i + constant::offsetEnemyX, constant::sizeSquare * j + constant::offsetEnemyY));
            window.draw(*rectangle);
        }
    }
}
void FightScene::eventHandler(const sf::Event* event, const sf::RenderWindow& window) {
    if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (MousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            
            if (worldPos.x > constant::offsetEnemyX && worldPos.x <constant::offsetEnemyX + constant::sizeSquare * 10
                && worldPos.y > constant::offsetEnemyY && worldPos.y < constant::offsetEnemyY + constant::sizeSquare * 10) {
                int x = (worldPos.x - constant::offsetEnemyX) / constant::sizeSquare;
                int y = (worldPos.y - constant::offsetEnemyY) / constant::sizeSquare;
                game->shootField(x, y);
            }
        }
    }
}