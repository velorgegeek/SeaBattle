#include "Game.h"
#include "DragBoat.h"
#include "constants.h"
#include <iostream>
void Game::setPos() {
    int count = dragboat.boat->countDeck;
    
    int i = round((dragboat.boat->rect.left - offsetX) / sizeSquare);
    int j = round((dragboat.boat->rect.top - offsetY) / sizeSquare);

    bool fits = false;
    if (i < 0 || j < 0 || i >9 || j>9) {
        if (dragboat.orient != dragboat.boat->orient) {
            dragboat.changeOrientation();
        }
        sf::FloatRect rect;
        auto pair_vec = dragboat.boat->cordinMap;
        if (pair_vec.empty()) {
            dragboat.boat->setPos(dragboat.getPos());
            dragboat.undrag();
            return;
        }
        if (dragboat.boat->orient == Boat::orientationBoat::Horizontal) {
            rect = sf::FloatRect(offsetX + pair_vec[0].first * sizeSquare,
                offsetY + pair_vec[0].second * sizeSquare,
                sizeSquare * dragboat.boat->countDeck,
                sizeSquare);
        }
        else {
           rect = sf::FloatRect(offsetX + pair_vec[0].first * sizeSquare,
                offsetY + pair_vec[0].second * sizeSquare,
                sizeSquare,
                sizeSquare * dragboat.boat->countDeck);

        }
        dragboat.boat->setPos(rect);

        setBoatToMap(pair_vec, dragboat.boat);
        setBlocked(pair_vec, Game::blockedCell::add);

        dragboat.undrag();
        return;
    }


    sf::Vector2f center;
    sf::FloatRect newRect;
    std::vector<std::pair<int, int>> vec;
    if (dragboat.boat->orient == Boat::orientationBoat::Horizontal)
    {
        if (i + dragboat.boat->countDeck <= 10)
        {
            vec = cordToMap(i, j, dragboat.boat);
            if (!checkIntersectBoat(vec)) {
                fits = true;
                newRect = sf::FloatRect(offsetX + i * sizeSquare,
                    offsetY + j * sizeSquare,
                    sizeSquare * dragboat.boat->countDeck,
                    sizeSquare);
            }
        }
    }
    else 
    {
        if (j + dragboat.boat->countDeck <= 10)
        {
            vec = cordToMap(i, j, dragboat.boat);
            if (!checkIntersectBoat(vec)) {
                fits = true;
                newRect = sf::FloatRect(offsetX + i * sizeSquare,
                    offsetY + j * sizeSquare,
                    sizeSquare,
                    sizeSquare * dragboat.boat->countDeck);
            }
        }
    }

    if (fits)
    {
        dragboat.boat->cordinMap = vec;
        setBoatToMap(vec, dragboat.boat);
        setBlocked(vec, Game::blockedCell::add);
        dragboat.boat->setPos(newRect);
    }else{
        if (dragboat.orient != dragboat.boat->orient) {
            dragboat.changeOrientation();
        }
        sf::FloatRect rect;
        auto pair_vec = dragboat.boat->cordinMap;
        if (pair_vec.empty()) {
            dragboat.boat->setPos(dragboat.getPos());
            dragboat.undrag();
            return;
        }
        if (dragboat.boat->orient == Boat::orientationBoat::Horizontal) {
            rect = sf::FloatRect(offsetX + pair_vec[0].first * sizeSquare,
                offsetY + pair_vec[0].second * sizeSquare,
                sizeSquare * dragboat.boat->countDeck,
                sizeSquare);
        }
        else {
            rect = sf::FloatRect(offsetX + pair_vec[0].first * sizeSquare,
                offsetY + pair_vec[0].second * sizeSquare,
                sizeSquare,
                sizeSquare * dragboat.boat->countDeck);

        }
        dragboat.boat->setPos(rect);

        setBoatToMap(pair_vec, dragboat.boat);
        setBlocked(pair_vec, Game::blockedCell::add);
    }
    dragboat.undrag();
}
void Game::setBoatToMap(const std::vector<std::pair<int, int>>& vec,  Boat* boat) {
    for (auto i : vec) {
        playerField[i.first][i.second].boat = boat;
    }
} 
void Game::changeOrientation(Boat* boat) {
    if (boat->countDeck == 0) {
        boat->changeOrientation();
        return;
    }
    int i = round((boat->rect.left - offsetX) / sizeSquare);
    int j = round((boat->rect.top - offsetY) / sizeSquare);

    setBlocked(boat->cordinMap, Game::blockedCell::remove);
    setBoatToMap(boat->cordinMap, nullptr);

    auto indexBoat = findOrientation(i, j, boat, (boat->orient == Boat::orientationBoat::Horizontal)
        ? Boat::orientationBoat::Vertical : Boat::orientationBoat::Horizontal);

    if (!indexBoat.empty()) {
        boat->cordinMap = indexBoat;
        boat->changeOrientation();
        boat->setPos(cordToPos(boat, indexBoat[0].first, indexBoat[0].second));
    }

    setBoatToMap(boat->cordinMap, boat);
    setBlocked(boat->cordinMap, Game::blockedCell::add);
   

}
sf::FloatRect Game::cordToPos(Boat* boat, int& i, int& j) {
    if (boat->orient == Boat::orientationBoat::Horizontal) {
         return sf::FloatRect(offsetX + i * sizeSquare,
            offsetY + j * sizeSquare,
            sizeSquare * boat->countDeck,
            sizeSquare);
    }
    else {
        return sf::FloatRect(offsetX + i * sizeSquare,
            offsetY + j * sizeSquare,
            sizeSquare,
            sizeSquare * boat->countDeck);
    }
}
void Game::hitToEnemyCheck(const int& i, const int& j) {
    if (enemyField[i][j] == 0) {
        //attack
    }
}
void Game::eventHandler(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            switch (gamestatus) {
            case GameStatus::none:
                for (auto i : manager.getBoats()) {
                    if (i->sprite.getGlobalBounds().contains(worldPos)) {
                        dragboat.dragBoat(i);
                        if (!dragboat.boat->cordinMap.empty()) {
                            setBoatToMap(dragboat.boat->cordinMap, nullptr);
                            setBlocked(dragboat.boat->cordinMap, Game::blockedCell::remove);
                        }
                        break;
                    }
                }
                break;
            case GameStatus::play:
                if((worldPos.x < offsetEnemyX || worldPos.x > offsetEnemyX + (sizeSquare * 10))
                    || (worldPos.y < offsetEnemyY || worldPos.y > offsetEnemyY + (sizeSquare * 10))) return;
                std::cout << static_cast<int>((worldPos.x - offsetEnemyX) / sizeSquare)<<std::endl;
                std::cout << static_cast<int>((worldPos.y - offsetEnemyY) / sizeSquare) << std::endl;
                break;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (timeRotate >= rotateTime) {
            timeRotate = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
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
    else if (event.type == sf::Event::MouseMoved) {
        if (dragboat.drag) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            dragboat.boat->setPos(sf::Vector2f{ worldPos.x, worldPos.y });
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (dragboat.drag) {
            setPos();
        }
    }
}
std::vector<Boat*> Game::getBoats() {
    return manager.getBoats();
}
bool Game::checkIntersectBoat( const std::vector<std::pair<int, int>>&  vec) {
    for (auto i : vec) {
        Cell c = playerField[i.first][i.second];
        if (c._status == Cell::status::blocked || c.boat != nullptr) {
            return true;
        }
    }
    return false;
}
void Game::setBlocked(const std::vector<std::pair<int, int>>& vec,Game::blockedCell status) {
    std::cout << std::endl << "Координаты:" << std::endl;
    for (auto i : vec) {
        std::cout << "x: " << i.first <<"y: "<< i.second<<std::endl;
    }
    std::vector<std::pair<int, int>> cord;
    for (auto i : vec) {
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                if (k == 0 && j == 0) {
                    continue;
                }
                int NewI = i.first + k;
                int NewJ = i.second + j;
                if (NewI < 0 || NewJ < 0 || NewI > 9 || NewJ > 9) {
                    continue;
                }
                if (playerField[NewI][NewJ].boat == nullptr) {
                    auto pair = std::make_pair(NewI, NewJ);
                    auto result = std::find(cord.begin(), cord.end(), pair);
                    if (result == cord.end()) {
                        cord.push_back(pair);
                    }
                }
            }
        }
    }
    for (auto i : cord) {
        if (status == Game::blockedCell::add) {
            playerField[i.first][i.second].upCountBlocked();
        }
        else {
            playerField[i.first][i.second].downCountBlocked();
        }
        //std::cout << "x:" << i.first << " y:" << i.second << " " << "green" << "\n"
        //    << "count: " << playerField[i.first][i.second].countBlocked << std::endl;
    }
}
std::vector<std::pair<int, int>> Game::findOrientation(int x, int y,const Boat* boat, Boat::orientationBoat status) {
    std::vector<std::pair<int, int>> indexBoat;
    int x1 = x;
    int y1 = y;
    int count = boat->countDeck;
    switch (status) {
    case Boat::orientationBoat::Horizontal:
        if (x1 + count-1 >9) {
            x1 -= (x1+count-1) -9;
        }
        for (int i = 0; i < count; i++) {
            if (i > 0) {
                y1++;
            }
            if (y1 > 9) {
                return {};
            }
            if (playerField[x1 + count-1][y1].boat == nullptr
                && playerField[x1 + count-1][y1]._status == Cell::status::none) {
                for (int k = 0; k < count; k++) {
                    int xk = x1 + k;
                    std::cout << xk << " " << y1 << std::endl;
                    if (xk>9) {
                        indexBoat.clear();
                        break;
                    }
                    if (playerField[xk][y1].boat == nullptr && playerField[xk][y1]._status == Cell::status::none) {
                        indexBoat.push_back(std::make_pair(xk, y1));
                    }
                    else {
                        indexBoat.clear();
                        break;
                    }
                }
            }
            if (!indexBoat.empty()) {
                return indexBoat;
            }
        }
        break;
    case Boat::orientationBoat::Vertical:
        if (y1 + count - 1 > 9) {
            y1 -= (y1 + count - 1) - 9;
        }
        for (int i = 0; i <count; i++) {
            if (i > 0) {
                x1++;
            }
            if (x1 > 9) {
                return {};
            }
            if (playerField[x1][y1 + count - 1].boat == nullptr
                && playerField[x1][y1 + count - 1]._status == Cell::status::none) {
                for (int k = 0; k < count; k++) {
                    int yk = y1 + k;
                    std::cout << x1 << " " << yk << std::endl;
                    if (yk > 9) {
                        indexBoat.clear();
                        break;
                    }
                    if (playerField[x1][yk].boat == nullptr && playerField[x1][yk]._status == Cell::status::none) {
                        indexBoat.push_back(std::make_pair(x1,yk));
                    }
                    else {
                        indexBoat.clear();
                        break;
                    }

                }
            }
            if (!indexBoat.empty()) {
                return indexBoat;
            }
        }
        break;
    }
    return indexBoat;
}
std::vector<std::pair<int, int>> Game::cordToMap(int x,int y,const Boat* boat) {
    std::vector<std::pair<int, int>> indexBoat;
    int count = boat->countDeck;
    switch (boat->orient) {
    case Boat::orientationBoat::Horizontal:
        for (int k = 0; k < count; k++) {
            int xk = x + k;
            if (xk < 0 || xk>9) {
                return {};
            }
            indexBoat.push_back(std::make_pair(xk, y));
        }
        break;
    case Boat::orientationBoat::Vertical:
        for (int k = 0; k < count; k++) {
            int yk = y + k;
            if (yk < 0 || yk>9) {
                return {};
            }
            indexBoat.push_back(std::make_pair(x, yk));
        }
        break;
    }
    return indexBoat;
}
void Game::initField() {
    playerField.resize(10, std::vector<Cell>(10));
    enemyField.resize(10, std::vector<int>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            enemyField[i][j] = 0;
        }
    }
}
void Game::updateTimerRotate(float time) {
    float deltaSeconds = time / 1000000.0f;
    timeRotate += deltaSeconds;
}
Game::Game() {
    initField();
}