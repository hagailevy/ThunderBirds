#pragma once
#include "Point.h"
class Board;

class Ghost
{
	Point _pos;
	char		_ch;
	Board* _pBoard;

	char _movingMode;
	int _xDiff = 0;
	int _yDiff = 0;

	bool _hitShip = false;


public:
	Ghost(Point pos, char ch = Signs::Ghost,  Board* pBoard = nullptr, char movingMode = GhostType::Vertical);
	void setBoard(Board* pBoard);
	void draw() const { printCharAtxy(_pos.x, _pos.y, _ch); }
	void del() const { printCharAtxy(_pos.x, _pos.y, Signs::Space); }

	void removeFromBoard();
	void putOnBoard();
	bool move();

	void setHitShip(bool hitShip) { _hitShip = hitShip; }
	bool getHitShip() { return _hitShip; }
private:
	void addDiffToPoints();
};

