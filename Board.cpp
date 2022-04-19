#include "Board.h"

/*
* Constarctor
*/
Board::Board()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width ; x++)
			if (y == 0 || x == 0 || y == Height - 1 || x == Width - 1)
				board[y][x] = Signs::Brick;
			else board[y][x] = Signs::Space;
	}
}

/*
* his function puts the frame of the game into an array.
*/
void Board::firstDraw() {
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			cout << board[y][x];
		}
		
		cout << endl;
	}

	
	//TODO - print lives, ticks etc...
	cout << "\tTime Left:" << endl;
	cout << "\tRemaining Lives:";

}
/*
* boolean function that checks if there is nothing in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/
bool Board::isEmpty(Point pos) {
	//TODO: ' ' should be a constant
	return (board[pos.y][pos.x] == Signs::Space);
}
/*
* boolean function that checks if there is a wall in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/
bool Board::isWall(Point pos) {
	//TODO: 'W' should be a constant 
	return (board[pos.y][pos.x] == Signs::Brick);
}
/*
* boolean function that checks if there is a block point in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/

bool Board::isBlock(Point pos) {
	return (board[pos.y][pos.x] >= '0' && board[pos.y][pos.x] <= '9');
}
/*
* boolean function that checks if there is an exit point in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/
bool Board::isExit(Point pos)
{
	return (board[pos.y][pos.x] == Signs::EXIT);
}
/*
* boolean function that checks if there is a ship in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/
bool Board::isShip(Point pos)
{
	return (board[pos.y][pos.x] == Signs::BigSign || board[pos.y][pos.x] == Signs::SmallSign);
}
/*
* boolean function that checks if there is a ghost in some location
* @parm Point pos -> the location to check.
* @return T/F.
*/
bool Board::isGhost(Point pos)
{
	return (board[pos.y][pos.x] == Signs::Ghost);
}
/*
* This function set the Two-dimensional table of the game.
*/
void Board::setLevel1()
{

	const char b = Signs::Brick;

	for (int c = 65; c < 80; c++)
	{
		board[3][c] = b;
		board[19][c] = b;
		if (c > 68)
		{
			board[6][c] = b;
			board[14][c] = b;

		}

	}
	for (int r = 14; r < 19; r++)
	{
		board[r][65] = b;
		board[22 - r][65] = b;
	}

	for (int c = 1; c < 17; c++)
	{
		board[9][c] = b;
		board[11][c] = b;
		board[14][c] = b;

		board[9][c + 40] = b;
		board[11][c + 40] = b;
		board[14][c + 40] = b;

	}

	for (int r = 14; r < 19; r++)
	{
		board[r][16] = b;
	}
	

	for (int r = 5; r < 21; r++)
		board[r][25] = b;


	for (int r = 1; r < 8; r++)
	{
		board[r][40] = b;
		if (r != 7)
			board[22 - r][40] = b;
	}

	for (int i = 1; i <= 6; ++i) {
		for (int j = 1; j <= i; ++j)
		{
			board[i + 13][j + 50] = b;
			board[j][i + 50] = b;
		}
	}
	for (int i = 7; i <= 20; ++i) {
		board[i][35] = b;
	}

	
}
//void Board::setExit(int e = 70, int x = 71, int i = 72, int t = 73, int row = 19)
void Board::setExit(int row, int col) 
{

	board[row][col] = Signs::EXIT;
}


/*
* goes to the last cord on the boar.d
*/
void Board::gotoEndBoard()
{
	gotoxy(Height, Width - 1);

}
