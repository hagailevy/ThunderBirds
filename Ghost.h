#pragma once
#include "Point.h"
class Board;

class Ghost
{
	Point _pos;
	char		_ch = Signs::Ghost;
	Board* _pBoard = nullptr;

public:
	Ghost(Point pos, char ch) : _pos(pos), _ch(ch) {}
	void setBoard(Board* pBoard);
	void draw() const { printCharAtxy(_pos.x, _pos.y, _ch); }
	void del() const { printCharAtxy(_pos.x, _pos.y, Signs::Space); }

	void removeFromBoard();
	void putOnBoard();

private:
	void addDiffToPoints(int xDiff, int yDiff);
};

