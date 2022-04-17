#include <iostream>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "utils.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
/*
* this function prints a single char at some cord.
* @parm int x.
* @parm int y.
* @parm char ch
* place the char at (x,y)
*/
void printCharAtxy(int x, int y, char ch)
{
	gotoxy(x, y);
	std::cout << ch;
}

// function definition -- requires process.h
void clrscr()
{
	system("cls");
}

void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
