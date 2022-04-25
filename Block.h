#pragma once
#include "Point.h"
class Board;
class Ship;


class Block
{
	vector<Point> _pointsVec;
	int			_numPoints = 0;
	char		_ch = Signs::Block;
	Board*		 _pBoard = nullptr;
	bool		_hasMoved = false;

	Ship* _shipToMoveWith = nullptr;


public:
	Block(vector<Point> pointsVec, int size, char ch);
	Block(const Block& other);
	Block& operator=(const Block& other) = delete;
	~Block();


	void setShipToMoveWith(Ship* ship) { _shipToMoveWith = ship; }
	Ship* getShipToMoveWith()const { return _shipToMoveWith; }


	void setHasMoved(bool status);
	bool getHasMoved()const;
	void SetBoard(Board* pBoard);
	void draw() const;
	void del() const;
	char getCh(char ch)const ;
	int getSize() const;
	bool move(int xDiff, int yDiff, int maxPower, vector<Block*>& vec);
	void putOnBoard();
	void removeFromBoard();
	bool isInBlock(Point p);
	char gravity();
	friend int findBlockIndex(Point p, vector<Block*>& vec);


	void addDiffToPoints(int xDiff, int yDiff);
};


