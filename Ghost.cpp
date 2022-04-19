#include "Ghost.h"
#include "Board.h"

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



void Ghost::addDiffToPoints(int xDiff, int yDiff)
{
	_pos.x+=xDiff;
	_pos.y += yDiff;
}

