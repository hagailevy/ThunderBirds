#include "Ghost.h"
#include "Board.h"

Ghost::Ghost(Point pos, char ch, Board* pBoard, char movingMode)
	: _pos(pos), _ch(ch), _pBoard(pBoard), _movingMode(movingMode)
{
	switch (_movingMode)
	{
	case(GhostType::Horizonal):
		_xDiff = 1;
		break;
	case (GhostType::Vertical):
		_yDiff = 1;
		break;
	case(GhostType::Wandering):
		break;
			


	}

}

void Ghost::setBoard(Board* pBoard) { _pBoard = pBoard; }


void Ghost::putOnBoard()
{
		_pBoard->board[_pos.y][_pos.x] = _ch;
	
}


/*
* update the board.
*/
void Ghost::removeFromBoard()
{

	_pBoard->board[_pos.y][_pos.x] = Signs::Space;;
	
}



void Ghost::addDiffToPoints()
{
	_pos.x +=_xDiff;
	_pos.y += _yDiff;
}

bool Ghost::move() {

	Point nextPos(_pos.x + _xDiff, _pos.y + _yDiff);
	if (_pBoard->isShip(nextPos))
	{
		_hitShip = true;
		return false;
	}
	if (_pBoard->isBlock(nextPos) || _pBoard->isWall(nextPos) || _pBoard->isExit(nextPos) || _pBoard->isGhost(nextPos)) // case: next move = wall
	{
		if (_yDiff != 0) // change ghost direction!
			_yDiff *= -1;
		else _xDiff *= -1;
		return false;
	}


	// if arrives here, then loop has ended - ghost can move forward.
	this->removeFromBoard();
	this->del();
	this->addDiffToPoints();
	this->putOnBoard();
	this->draw();
	return true;



}
