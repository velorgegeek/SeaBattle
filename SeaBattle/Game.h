#pragma once
#include "BoatManager.h"
#include "Cell.h"
#include "DragBoat.h"
#include <vector>
#include "RequestToServer.h"
#include <unordered_map>
#include <string>
#include "GameScenes.h"

class Game {
private:
    std::unordered_map<std::string, Scene*> GameScenes;

   Scene* scene = new PrepareScene(this);
    //Scene* scene = new FightScene(this);
    RequestToServer request;
    enum class GameStatus { none, play };
    //none,play,waiting,prepare
    BoatManager manager;
    DragBoat dragboat;
    GameStatus gamestatus = GameStatus::none;

    enum class blockedCell { add, remove };
    void setBlocked(const std::vector<std::pair<int, int>>& vec, Game::blockedCell status);
    void setPos();
    void changeOrientation(Boat* boat);
    std::vector<std::pair<int, int>> findOrientation(const int& x, const int& y, const Boat* boat, Boat::orientationBoat status);
    void initField();
    void setBoatToMap(const std::vector<std::pair<int, int>>& vec, Boat* boat);
    bool checkIntersectBoat(const std::vector<std::pair<int, int>>& vec);
    sf::FloatRect cordToPos(Boat* boat, int& i, int& j);
    std::vector<std::pair<int, int>> cordToMap(const int& x, const int& y, const Boat* boat);
    void hitToEnemyCheck(const int& i, const int& j);

public:

    float timeRotate;
    Boat* getDragBoat();
    std::vector<Boat*> getBoats() const;
    void drag(Boat* boat);

    int getCountBoatOnMap() {return manager.boatOnMap;}
    bool IsDraging();
    void setPosBoat();
    void changeOrientationBoat(Boat* boat);
    void updateTimerRotate(float time);

    void shootField(const int& x,const int& y);
    std::vector<std::pair<int, int>> cordToMap();

    std::vector<std::vector<Cell>> playerField;
    std::vector<std::vector<int>> enemyField;

    void draw(sf::RenderWindow& window);
    void eventHandler(const sf::Event* event, const sf::RenderWindow& window);
    Game();
};