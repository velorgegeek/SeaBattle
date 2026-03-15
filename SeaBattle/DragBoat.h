#pragma once
#include <SFML/Graphics.hpp>
#include "Boat.h"
#include "constants.h"
#include <vector>
#include <iostream>
struct DragBoat {
public:
    Boat* boat;
    sf::Vector2f startPos;
    bool drag = false;
    Boat::orientationBoat orient;
    std::vector < std::pair<int,int>> indexBoat;
    DragBoat() {};
    void changeOrientation() {
        boat->changeOrientation();
    }
    void setIndex(const std::vector < std::pair<int, int>>& vec) {
        indexBoat = vec;
    }
    void dragBoat(Boat* boat) {
        this->boat = boat;
        orient = boat->orient;
        startPos = boat->sprite.getPosition();
        drag = true;
    }
    void undrag() {
        boat = nullptr;
        drag = false;
    }
    sf::Vector2f getPos()const { return startPos; }
};