#pragma once
#include "Point.h"
class Board;

class Ghost
{
	Point _pos;
	char		_ch = Signs::Ghost;
	Board* _pBoard = nullptr;

	int _xDiff = -1;
	int _yDiff = 0;

	bool _hitShip = false;
public:
	Ghost(Point pos, char ch) : _pos(pos), _ch(ch) {}
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

