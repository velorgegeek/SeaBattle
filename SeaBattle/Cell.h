#pragma once
class Boat;
class Cell {
public:
	Boat* boat = nullptr;
	enum class status { none, hitted, blocked, hittedBoat,diedZone};
	int countBlocked = 0;
	status _status = Cell::status::none;
	void upCountBlocked();
	void downCountBlocked();
	Cell() {};
	Cell(Boat* boat) : boat(boat) {};
};