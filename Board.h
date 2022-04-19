#pragma once

#include "Point.h"




class Board
{
public:
	constexpr static int menuSize = 3;
	constexpr static int Width = 80;
	constexpr static int Height = 25 - menuSize;
//private:
	char board[Height][Width];
public:
	Board();
	//TODO - maybe no need for both get and getCharAt
	char get(int x, int y) const {
		return board[y][x];
	}
	void set(int x, int y, char c) {
		board[y][x] = c;
	}
	char getCharAt(Point pos) {
		//TODO - handle out of matrix bounds
		return board[pos.y][pos.x];
	}

	void firstDraw();
	bool isEmpty(Point pos);
	bool isWall(Point pos);
	bool isBlock(Point pos);
	bool isExit(Point pos);
	bool isShip(Point pos);
	bool isGhost(Point pos);
	void setLevel1();
	void setExit(int row = 7, int col = 76);
	void gotoEndBoard();


};