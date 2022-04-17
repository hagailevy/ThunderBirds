#include <iostream>

#include "utils.h"
#include "Game.h"

int main()
{
	hide_cursor();
	clrscr();
	//TODO - change back to normal sleep
	//Game g;
	Game g(GameConstants::NormalSleep);
	g.run();

}