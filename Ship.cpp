#include "Ship.h"
#include "Board.h"
#include "Block.h"
/*
* Constractor :
* @parm Point* pointsArr - > an arr of point objects.
* @parm int size - > the size of the Points arr.
* @parm char ch -> a char that represent the type of the object.
* @parm int power - > the power of the ship
*/
Ship::Ship(vector<Point> pointsVec, int size, char ch, int power) :_pointsVec(pointsVec), _numPoints(size), _ch(ch), _power(power)
{
}
/*
* Copy constractor.
*/
Ship::Ship(const Ship& other)
{
	this->_pointsVec = other._pointsVec;
	this->_numPoints = other._numPoints;
	this->_ch = other._ch;
	this->_power = other._power;
	this->_pBoard = other._pBoard;
	this->_hitGhost = other._hitGhost;
	this->_exitArrived = other._exitArrived;

}
/* void function that set the board.
* @parm Board* pBoard ->a pointer to a Board object.
* the function sets the data member _pBoard to the pboard.
*/
void Ship::SetBoard(Board* pBoard)
{
	_pBoard = pBoard;
}
/*
* const function .
* @retrun _power -> the power of the ship.
*/
int Ship::getPower() const
{
	return _power;
}

/*
* this is a void function that set the data member _pBlockToCarry.
*
*/
void Ship::setCarrier(Block* p)
{
	_pBlockToCarry = p;
}

/*
* return pointer  of the carrier.
*
* return Block*
*/
Block* Ship::getCarrier() const
{
	return _pBlockToCarry;
}

/*
* Draw a ship .
*/
void Ship::draw() const {
	for (int i = 0; i < _numPoints; i++)
	{
		printCharAtxy(_pointsVec[i].x, _pointsVec[i].y, _ch);
	}
}
/*
* delete ship.
*/
void Ship::del() const {
	for (int i = 0; i < _numPoints; i++)
	{
		printCharAtxy(_pointsVec[i].x, _pointsVec[i].y, Signs::Space);
	}
}
/*
* check if the ship has arrived to exit point.
*/
bool Ship::arrivedExit() const
{
	return _exitArrived;
}
/*
* add diractions to Points.
* @parm int dir -> the direction to move.
*/
void Ship::addDiffToPoints(int xDiff, int yDiff) {

	for (int i = 0; i < _numPoints; i++)
	{
		_pointsVec[i].x += xDiff;
		_pointsVec[i].y += yDiff;
	}
}

/*
* move function, checks if ship can move, and if it does - returns true, otherwise returns false. also if hits a block, checks if it can move forwrd.
* @parm int xDiff -> the direction of ship (x value of direction).
* @parm int yDiff -> the direction of ship (y value of direction).
* @parm int maxPower -> the maximum power of the ship (for example - big ship 6, smallShip - 2)
* @parm  vector<Block*>& vec -> a reference to a vector variable of pointers to block, when ship move - function updates vector in relevant places.
*/
bool Ship::move(int xDiff, int yDiff, int maxPower, vector<Block*>& vec)
{
	for (int i = 0; i < _numPoints; i++) 
	{
		Point nextPos(_pointsVec[i].x + xDiff, _pointsVec[i].y + yDiff);

		if (_pBoard->isWall(nextPos)) // case: next move = wall
			return false;
		else if (_pBoard->isGhost(nextPos))
		{
			_hitGhost = true;
			return false;
		}
		else if (_pBoard->isExit(nextPos)) // case: next move = exit
		{
			this->removeFromBoard();
			_exitArrived = true;
			return false;
		}
		else  if (_pBoard->isShip(nextPos) && _pBoard->getCharAt(nextPos) != _ch) // case: next move = other ship
			return false;
	}

	////check carry move and remove the carry of we mithakech bakir
	//if (_pBlockToCarry != nullptr) //case block fell on ship - then ship needs to carry it
	//{
	//	if (yDiff >= 0) //only for right and left and down (otherwise block already moved)
	//	{
	//		if (!_pBlockToCarry->move(xDiff, yDiff, _sShip->getPower(), _blocksVec))
	//		{
	//			_sShip->setCarrier(nullptr);
	//		}
	//	}
	//}

	for (int i = 0; i < _numPoints; i++)
	{
		Point nextPos(_pointsVec[i].x + xDiff, _pointsVec[i].y + yDiff);

		if (_pBoard->isBlock(nextPos)) // case: next move = block
		{
			int idx = findBlockIndex(nextPos, vec);
			if (idx != -1)
			{
				if (maxPower <= 0) // case: ship can not move the block
					return false;
				else if (vec[idx] != _pBlockToCarry)
				{
					// recursive - check for more blocks to push:
					bool res = vec[idx]->move(xDiff, yDiff, maxPower - vec[idx]->getSize(), vec);
					if (res == false)
						return false;
				}
			}
		}
	}
	// if arrives here, then loop has ended - all points will hit space, ship can move forward.
	this->removeFromBoard();
	this->del();
	this->addDiffToPoints(xDiff, yDiff);
	this->draw();
	this->putOnBoard();
	return true;


}

/*
* this function place the ship cords on the board..
*/
void Ship::putOnBoard()
{
	for (int i = 0; i < _numPoints; i++)
	{
		_pBoard->board[_pointsVec[i].y][_pointsVec[i].x] = _ch;
	}
}
/*
* this function remove the ship cord from the board.
*/
void Ship::removeFromBoard()
{
	for (int i = 0; i < _numPoints; i++)
	{
		_pBoard->board[_pointsVec[i].y][_pointsVec[i].x] = Signs::Space;;
	}
}




/*
* destractor.
*/
Ship::~Ship()
{

}

