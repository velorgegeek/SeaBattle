#pragma once
#include "BoatManager.h"
#include "Cell.h"
#include "DragBoat.h"
#include <vector>
class Game {
private:
        enum class blockedCell { add, remove };
        BoatManager manager;
        DragBoat dragboat;
        void setBlocked(const std::vector<std::pair<int, int>>& vec, Game::blockedCell status);
        void setPos();
        void changeOrientation(Boat* boat);
        std::vector<std::pair<int, int>> findOrientation(int x, int y, const Boat* boat, Boat::orientationBoat status);
        void initField();
        void setBoatToMap(const std::vector<std::pair<int, int>>& vec, Boat* boat);
        bool checkIntersectBoat(const std::vector<std::pair<int, int>>& vec);
        sf::FloatRect cordToPos(Boat* boat, int& i, int& j);
        std::vector<std::pair<int, int>> cordToMap(int x, int y, const Boat* boat);
public:
        std::vector<Boat*> getBoats();
        std::vector<std::vector<Cell>> playerField;
        std::vector<std::vector<int>> enemyField;
        std::vector<std::pair<int, int>> cordToMap();

        void eventHandler(const sf::Event& event, const sf::RenderWindow& window);
        Game();
};