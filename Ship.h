#pragma once
#include "Point.h"

class Board;
class Block;
struct Point;

class Ship
{
	vector<Point> _pointsVec;
	int			_numPoints;
	char		_ch;
	Board*		_pBoard = nullptr;
	bool _hitGhost = false;
	bool		_exitArrived = false;
	int _power = 0;
	Block* _pBlockToCarry = nullptr;

	vector<Block*> _blocksToCarryVec;
	int _carriedBlocksWeight = 0;


public:
	
	Ship(vector<Point> pointsVec, int size, char ch, int power);
	Ship& operator=(const Ship& other) = delete;
	Ship(const Ship& other);
	~Ship();

	void initBlockToCarryVector(int numBlocks);
	void setCarrierAtIndex(int index, Block* carrier) { _blocksToCarryVec[index] = carrier; }
	int getCarriedBlocksWeight() const { return _carriedBlocksWeight; }

	void displayMovedBlocks();
	void deleteMovedBlocks();

	char getCh() const { return _ch; }
	void SetBoard(Board* pBoard);
	void setCarrier(Block* p);
	Block* getCarrier() const;
	int getPower() const;
	void draw() const;
	void del() const;
	bool move(int xDiff, int yDiff, int maxPower, vector<Block*>& vec);
	
	void putOnBoard();
	void removeFromBoard();
	bool arrivedExit() const;

	void setHitGhost(bool hitGhost) { _hitGhost = hitGhost; }
	bool getHitGhost() { return _hitGhost;  }
private:
	void addDiffToPoints(int xDiff, int yDiff);
	void moveCarriers(int xDiff, int yDiff);
};

