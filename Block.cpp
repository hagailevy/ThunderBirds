#include "Block.h"
#include "Board.h"
/*
* constractor
* @parm Points* pointsArr -> An array of Points.
* @parm int size -> the size of the arr.
* @parm char ch -> the character that represent the block obj.
*
*/
Block::Block(vector<Point> pointsVec, int size, char ch) : _pointsVec(pointsVec), _numPoints(size), _ch(ch) {

}
/*
* copy Constractor.
*/
Block::Block(const Block& other)
{
	this->_numPoints = other._numPoints;
	this->_ch = other._ch;
	this->_pBoard = other._pBoard;
	this->_pointsVec = other._pointsVec;
}

/*
* destractor.
*/
Block::~Block()
{

}


/*
* set the data member hasmoved.
*/
void Block::setHasMoved(bool status)
{
	_hasMoved = status;
}

/*
* check if there is any changed on the block.
*
* @return bool
*/
bool Block::getHasMoved() const
{
	return _hasMoved;
}
char Block::getCh(char ch)const { return _ch; }

int Block::getSize() const { return _numPoints; }
void Block::SetBoard(Board* pBoard) { _pBoard = pBoard; }

/*
* draw the block on the screen.
*/
void Block::draw() const 
{
	for (int i = 0; i < _numPoints; i++)
	{
		printCharAtxy(_pointsVec[i].x, _pointsVec[i].y, _ch);
	}
}

/*
* remove the block from the screen.
*/
void Block::del() const
{
	for (int i = 0; i < _numPoints; i++)
	{
		printCharAtxy(_pointsVec[i].x, _pointsVec[i].y, Signs::Space);
	}
}

/*
* update the board.
*/
void Block::putOnBoard()
{
	for (int i = 0; i < _numPoints; i++)
	{
		_pBoard->board[_pointsVec[i].y][_pointsVec[i].x] = _ch;
	}
}


/*
* update the board.
*/
void Block::removeFromBoard()
{
	for (int i = 0; i < _numPoints; i++)
	{
		_pBoard->board[_pointsVec[i].y][_pointsVec[i].x] = Signs::Space;;
	}
}

/*
* this is boolean function that check if obj Point is owned by this Block.
* @parm Point p -> acopy of the point to check.
* @return bool.
*/
bool Block::isInBlock(Point p)
{

	for (int i = 0; i < _numPoints; i++)
	{

		if (p.x == _pointsVec[i].x && p.y == _pointsVec[i].y)
			return true;
	}

	return false;

}

/*
* this is a char function that manage the  gravity of the game
* @return char - > the char represent the status of the
* internal parms:
*@Point dest->the destenion of the next move for gravity.
* @parm char fellon ->
* @parm
*/
char Block::gravity()
{
	Point dest;
	for (int i=0; i < _numPoints ; i++)
	{
		dest = _pointsVec[i];
		dest.y++;
		if (_pBoard->isWall(dest) || _pBoard->isShip(dest) || (_pBoard->isBlock(dest) && _pBoard->getCharAt(dest) != _ch))
			return _pBoard->getCharAt(dest); //fell on the floor or on a ship (brick)
	}

	// otherwise: keep falling!!

	_hasMoved = true;
	this->del();
	for (int i = 0; i < _numPoints; i++)
	{
		removeFromBoard();
		_pointsVec[i].y++;
		putOnBoard();
	}
	this->draw();
	return Signs::Space;

}
/*
* This is a boolean recurive function .
* @parm int xDiff -> if there is change in Axis X(in case not xDiff=0)
* @parm int yDiff -> if there is a change in Axis y (in case not yDiff=0)
* @parm int maxPower - the power of the ship that is moving.
* @parm vector<Block*>& vec -> a vector<Block*> refferance that owns a pointer to the whole blocks in game.
* @return bool True/false -> if the block has moved successfuly .
* The function check recursivly on the block if there is wall/ship/block at the next move.
* in case it is a block,the function continues  recrusively calls.
* 
*/
bool Block::move(int xDiff, int yDiff, int maxPower, vector<Block*>& vec)
{
	if (maxPower < 0)
		return false;


	for (int i = 0; i < _numPoints; i++)
	{

		Point nextPos(_pointsVec[i].x + xDiff, _pointsVec[i].y + yDiff);

		if (_pBoard->isWall(nextPos)) // case: next move = wall
			return false;
		else if (_pBoard->isExit(nextPos)) // case: next move = exit - block can not exit
			return false;
		else if (_pBoard->isShip(nextPos))
			return false;
		else if (_pBoard->isBlock(nextPos) && !isInBlock(nextPos)) // case: next move = block (not this one itself)
		{
			int idx = findBlockIndex(nextPos, vec);
			if (idx != -1)
			{
				if (maxPower <= 0) // case: ship can not move the block
					return false;
				else
				{
					// recursive - check for more blocks to push:
					bool res = vec[idx]->move(xDiff, yDiff, maxPower - ( vec[idx]->getSize() ), vec);
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
		this->putOnBoard();
		this->draw();
		return true;
}

/*
* add diractions to points
* @parm int dir.
*
*/
void Block::addDiffToPoints(int xDiff, int yDiff)
{

	for (int i = 0; i < _numPoints; i++)
	{
		_pointsVec[i].x += xDiff;
		_pointsVec[i].y += yDiff;
	}
}

/*
* This function helps to find single block in vector<block*>
* @parm Point p -> the point to look for.
* @parm vector<Block*>& vec -> a refference to a vector<Block*> 
* @return int -> the index in the vector.
*/
int findBlockIndex(Point p, vector<Block*>& vec) {

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->isInBlock(p))
			return i;
	}
	return -1;
}