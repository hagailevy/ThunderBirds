#pragma once
#include <vector>
#include <iostream>

void gotoxy(int, int);
void clrscr();
void hide_cursor();
void printCharAtxy(int x, int y, char ch);
using namespace std;

struct Keys {
	constexpr static char ESC = 27;
	constexpr static char Up = 'w';
	constexpr static char Right = 'd';
	constexpr static char Down = 'x';
	constexpr static char Left = 'a';
	constexpr static char _Small = 's';
	constexpr static char _Big = 'b';
	constexpr static char Instructions = '8';
	constexpr static char ExitKey = '9';
	constexpr static char StartGame = '1';

	
	constexpr static int Small = 0;
	constexpr static int Big = 1;
}; 

struct Signs {

	constexpr static char BigSign = '@';
	constexpr static char SmallSign = '$';
	constexpr static char Space = ' ';
	constexpr static char Brick = (char)177;
	constexpr static char Block = '1';
	constexpr static char EXIT = 'E';
	constexpr static char Heart = (char)3;
};

struct Sizes {
	constexpr static int InGameScreens_HEIGHT = 6;
	constexpr static int InGameScreens_WIDTH = 52;
	constexpr static int BigPower = 6;
	constexpr static int SmallPower = 3;
};

struct MoveDestType {
	constexpr static int Wall = 0;
	constexpr static int Empty = 1;
	constexpr static int Exit = 2;
	constexpr static int Block = 3;
	constexpr static int Ship = 4;
};
