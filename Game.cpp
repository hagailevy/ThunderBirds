﻿#include <conio.h>
#include <cctype>
#include <windows.h>
#include <iostream>
#include<fcntl.h>
#include <io.h>
#include <fstream>
#include <string.h>
#include "Game.h"

/*
* constractor for the object Game
* @parm int sleepInterval - > set the speed of the game.
*/
Game::Game(int sleepInterval)
	:_sleepInterval(sleepInterval)
{


	//init ships
	vector<Point> bigShipPoints({ { 6,17 },  { 7 , 17 } , { 6 , 18}, { 7,18 } });
	_bShip = new Ship(bigShipPoints, 4, Signs::BigSign, Sizes::BigPower);
	_bShip->SetBoard(&board);

	vector<Point> smallShipPoints({ {6,10}, {7,10} });
	_sShip = new Ship(smallShipPoints, 2, Signs::SmallSign, Sizes::SmallPower);
	_sShip->SetBoard(&board);

	//init blocks - TODO: dtors
	vector<Point> block1Points({ {42,12}, {43,12} , {44, 12}, { 42,13}, {43, 13}, { 44,13} });
	Block* block1 = new Block(block1Points, 6, '4');

	vector<Point> block2Points({ {25,1} , {25, 2}, { 25,3 },  { 25,4}, {26,1} });
	Block* block2 = new Block(block2Points, 5, '2');


	vector<Point> block3Points({ { 40,8 },{41,8} });
	Block* block3 = new Block(block3Points, 2, '3');

	vector<Point> block4Points({ { 11, 10 } });
	Block* block4 = new Block(block4Points, 1, '1');

	vector<Point> block5Points({ { 48,13 } });
	Block* block5 = new Block(block5Points, 1, '5');

	vector<Point> block6Points({ { 11,6 },{ 11,5 } });
	Block* block6 = new Block(block6Points, 2, '6');



	_blocksVec.push_back(block1);
	_blocksVec.push_back(block2);
	_blocksVec.push_back(block3);
	_blocksVec.push_back(block4);
	_blocksVec.push_back(block5);
	_blocksVec.push_back(block6);
	_numBlocks = _blocksVec.size();

	for (int i = 0; i < _numBlocks; i++)
	{
		_blocksVec[i]->SetBoard(&board);
	}


	Ghost* ghost1 = new Ghost({ 5,10 }, Signs::Ghost);
	_ghostsVec.push_back(ghost1);
	_numGhosts = _ghostsVec.size();

	for (int i = 0; i < _numGhosts; i++)
	{
		_ghostsVec[i]->setBoard(&board);
	}


	_sShip->initBlockToCarryVector(_numBlocks);
	_bShip->initBlockToCarryVector(_numBlocks);

}
Game::Game(const Game& other)
{
	// TODO: copy ctor!!


}
void Game::readFromFilesOrdered() {
	string name = "tb_";
	string end = ".screen";
	string fileName = name + _fileNum + end;
	
	ifstream currentFile(fileName);

	if (!currentFile.is_open() || _fileNum <= 'z') {
		_fileNum++;
		fileName = name + _fileNum + end;
		currentFile.open(fileName, std::ios_base::in);

	}

	


}


void Game::printBadFile(const string& fileName)
{
	clrscr();
	cout << "\n\t\t Sorry, following file is missing: " << fileName << endl;
	cout << "\t Press any key to continue for the next (lexicographically) file...";




}


void Game::loadScreen(const ifstream& file)
{
	string line;

	


}


/*
* This function handle the user options for the menu.
*/
void Game::chooseOptions()
{

	printMenu();
	char key = 0;
	while (!key)
	{

		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case(Keys::StartGame):
				//readFromFilesOrdered();
				break;
			case(Keys::Instructions):
				printInstructions();
				key = 0;
				printMenu();
				break;
				
			case(Keys::ExitKey):
				_exit = true;
				break;
			default: key = 0;
			}
		}
	}
	clrscr();

}
/*
* this is a void function that prints the usermenu to the screen.
*/
void Game::printMenu()const {
	clrscr();
	/*cout << "\n\t\t   Welcome to ThunderBirds!" << endl << endl;
	cout << "\t\ta) Click 1 to start a new game." << endl;
	cout << "\t\tb) Click 8 for instructions and keys." << endl;
	cout << "\t\tc) Click 9 to exit." << endl;*/

	static char menuScreen[Sizes::BoardHeight][Sizes::BoardWidth] =
	{       "******************************************************************************\n",
			"*                      Welcome to ThunderBirds!                              *\n",
			"*                                                                            *\n",
			"*                  a) Click 1 to start a new game.                           *\n",
			"*                  b) Click 2 to load game from a specific file.             *\n",
			"*                  c) Click 3 to change color mode.                          *\n",
			"*                  d) Click 8 for instructions and keys.                     *\n",
			"*                  e) Click 9 to exit.                                       *\n",
			"*                                                                            *\n",
			"*     ~)*#########*                                                          *\n",
			"*       |##############                                                      *\n",
			"*          |##############.                                                  *\n",
			"*              |###########%%* .................                             *\n",
			"*              )##%(*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.                   *\n",
			"*             ),,,,,,,,,,,,,,,,,,,,,,,,,,,,,%%%*,,,,,,,,,,*####)             *\n",
			"*             /.,,,,,,,,,,,,,,,,,,,,,,,,#%%     %%%,,,,,,,,%#######)         *\n",
			"*         //###%%#####%%%%#(*,,,,,,,,,,%%.        %%/,,,,,,%##########)      *\n",
			"*    ~&&&&&&&&&&&&&&&&&&&&&&&&&(******&& .........&&*******&&&&&&&&&&&&)     *\n",
			"*            //************************(&& ....../&&*******&&&&&&&&&&)       *\n",
			"*             |**************************(&&&&&&&&*********&&&&&&&)          *\n",
			"*               |*****************************************/&&)               *\n",
			"*               )&&&&&&&#******************************                      *\n",
			"*            )&&&&&&&&&&&&&*                                                 *\n",
			"*         /&&&&&&&&&&&&&&                                                    *\n",
			"***   ~)&&&&&&&&&&&&&&.       ************************************************\0",
	};

	for (int r = 0; r < Sizes::BoardHeight; r++)
		{
			for (int c = 0; c < Sizes::BoardWidth; c++)
				cout << menuScreen[r][c];

		}
}
/*
* This function duplicate vector<Block*>
* @return vector<Block*>
*/
vector<Block*> Game::duplicateBlocksVec(vector<Block*> origVec)
{
	vector<Block*> newVec;
	for (int i = 0; i < origVec.size(); i++)
	{
		newVec.push_back(new Block(*(origVec[i])));
	}
	return newVec;
}


vector<Ghost*> Game::duplicateGhostsVec(vector<Ghost*> origVec)
{
	vector<Ghost*> newVec;
	for (int i = 0; i < origVec.size(); i++)
	{
		newVec.push_back(new Ghost(*(origVec[i])));
	}
	return newVec;
}
/*
* This function free all blocks from the vector of Block*
* @parm vector<Block*> -> the vector of blocks pointers to free.
*
*/
void Game::freeBlocksVec(vector<Block*> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		delete vec[i];
	}
	vec.clear();
}

void Game::freeGhostsVec(vector<Ghost*> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		delete vec[i];
	}
	vec.clear();
}


/*
* print all blocks in game.
*/
void Game::printBlocksVec()
{

	for (int i = 0; i < _numBlocks; i++)
	{
		_blocksVec[i]->draw();
		_blocksVec[i]->putOnBoard();
	}

}

void Game::printGhostsVec()
{

	for (int i = 0; i < _numGhosts; i++)
	{
		_ghostsVec[i]->draw();
		_ghostsVec[i]->putOnBoard();
	}

}

/*
* delete all blocks from the game.
*/
void Game::delBlocksVec()
{
	for (int i = 0; i < _numBlocks; i++)
	{
		_blocksVec[i]->del();
		_blocksVec[i]->removeFromBoard();
	}
}


void Game::delGhostVec()
{
	for (int i = 0; i < _numGhosts; i++)
	{
		_ghostsVec[i]->del();
		_ghostsVec[i]->removeFromBoard();
	}
}
/*
* set all blocks in game.
*/
void Game::setBlocksVec()
{

	for (int i = 0; i < _numBlocks; i++)
	{
		_blocksVec[i]->putOnBoard();
	}

}

void Game::setGhostsVec()
{

	for (int i = 0; i < _numGhosts; i++)
	{
		_ghostsVec[i]->putOnBoard();
	}

}
/*
* This is the "main" function for the game,from here we run the game.
*/
void Game::run()
{

	chooseOptions();

	while (!_exit) {


		board.setLevel1();
		board.setExit();
		board.firstDraw();
		printLives();

		Ship* pBigShipSaver = new Ship(*_bShip);
		Ship* pSmallShipSaver = new Ship(*_sShip);
		vector<Block*> blockSaverVec = duplicateBlocksVec(_blocksVec);
		vector <Ghost*> ghostSaverVec = duplicateGhostsVec(_ghostsVec);

		while (_lives > 0 && (!_bigArrived || !_smallArrived) && !_exit)
		{
			_sShip->draw();
			_bShip->draw();
			printBlocksVec();
			printGhostsVec();
			_bShip->putOnBoard();
			_sShip->putOnBoard();



			runKeys();
			if (_exit)
				break;


			//reset ships to orig positions -
			//TODO check if delete from screen is also needed
			delete _bShip;
			_bShip = pBigShipSaver;
			pBigShipSaver = new Ship(*_bShip);
			delete _sShip;
			_sShip = pSmallShipSaver;
			pSmallShipSaver = new Ship(*_sShip);
			_shipDir = 0;

			_bShip->setCarrier(nullptr);
			_sShip->setCarrier(nullptr);
			delBlocksVec();
			freeBlocksVec(_blocksVec);
			_blocksVec = duplicateBlocksVec(blockSaverVec);

			delGhostVec();
			freeGhostsVec(_ghostsVec);
			_ghostsVec = duplicateGhostsVec(ghostSaverVec);

		}

		delete pBigShipSaver;
		delete pSmallShipSaver;
		freeBlocksVec(blockSaverVec);
		freeGhostsVec(ghostSaverVec);

		if (_lives == 0)
		{
			printLossScreen();
		}

		if (_bigArrived && _smallArrived) // check if break because of level finishing or because of exiting game
		{
			printWinningScreen();
		}


		// in case all lives are over / user winned - init for next round:
		_lives = 3;
		_bigArrived = true;
		_smallArrived = false;

		if (!_exit) {
			chooseOptions();
		}

	}


}
/*
* this function handle the in
*/

void Game::runKeys()
{

	int countDown = GameConstants::CountdownPerLife;
	int timeCounter = 0;
	tickDown(timeCounter, countDown);

	bool toContinue = true;
	while (toContinue) {

		char key = 0;
		if (_kbhit()) {
			key = _getch();
			if (key == Keys::ESC)
			{
				toContinue = pauseGame();
				if (!toContinue)
				{
					_exit = true;
					break;
				}
				else {

					board.firstDraw();
					if (!_smallArrived) _sShip->draw();
					if (!_bigArrived) _bShip->draw();
					_shipDir = 0;
				}
			}
			hitKeys(key);
		}

		if (!gravitateAllBlocks())// all blocks have gravitated, if  "gravitateAllBlocks" is false - that means a block fell on a ship and killed it (death).
		{
			return;
		}
		if (!moveAllGhosts()) //all ghosts have moved, if moveAllGhosts is false - that means that a ghost have hit ship - then death...
		{
			return;
		}

		startMoving();

		if (_sShip->getHitGhost() || _bShip->getHitGhost())
		{
			death();
			printLives();
			return;
		}


		if (_bigArrived && _smallArrived)  // both ships have exited
			toContinue = false;

		timeCounter++;
		tickDown(timeCounter, countDown);
		if (countDown == 0)
		{
			death();
			printLives();
			break;
		}
		Sleep(_sleepInterval);
	}
}
/*
* set the data members when the player has died.
*/
void Game::death()
{
	_lives--;
	_bShip->del();
	_bShip->removeFromBoard();
	_sShip->del();
	_sShip->removeFromBoard();
	delBlocksVec();
	delGhostVec();
	_shipDir = 0;
}

/*
* this function manage the clock on the game.
*/
void Game::tickDown(int timeCounter, int& countDown)
{
	if (timeCounter % 10 == 0)
	{
		countDown--;


		gotoxy(20, 22);
		cout << "      ";
		gotoxy(20, 22);
		cout << countDown;


	}


}
/*
* This is a void function that print the lives on the screen.
*/
void Game::printLives()const {


	gotoxy(25, 23);
	cout << "      ";
	gotoxy(25, 23);

	for (int i = 0; i < _lives; i++)
		cout << Signs::Heart << " ";


}

/*
* Handle the user keys.
*/

void Game::hitKeys(char key) {
	switch (std::tolower(key)) {
	case (Keys::Up):
		_shipDir = Keys::Up;
		break;
	case (Keys::Down):
		_shipDir = Keys::Down;
		break;
	case (Keys::Right):
		_shipDir = Keys::Right;
		break;
	case (Keys::Left):
		_shipDir = Keys::Left;
		break;
	case (Keys::_Small):
		_activeShip = Keys::Small;
		_shipDir = 0;
		break;
	case (Keys::_Big):
		_activeShip = Keys::Big;
		_shipDir = 0;
		break;
	}

}
/*
* this function Moves the objects during the game.
*/
void Game::startMoving()
{
	int xDiff = 0, yDiff = 0;
	bool didMove;
	Block* carrier = nullptr;
	switch (_shipDir)
	{
	case (Keys::Up):
		yDiff = -1;
		break;
	case (Keys::Down):
		yDiff = 1;
		break;
	case (Keys::Left):
		xDiff = -1;
		break;
	case (Keys::Right):
		xDiff = 1;
		break;
	}



	if (_shipDir != 0)
	{
		if (_activeShip == Keys::Small && !_sShip->arrivedExit())
		{
			// preventing small ship to delete big ship
			if (!_bigArrived)
				_bShip->putOnBoard();

			didMove = _sShip->move(xDiff, yDiff, _sShip->getPower(), _blocksVec);
			//carrier = _sShip->getCarrier();
			//if (carrier != nullptr && didMove) //case block fell on ship - then ship needs to carry it
			//{
			//	if (yDiff >= 0) //only for right and left (otherwise block already moved)
			//	{
			//		if (!carrier->move(xDiff, yDiff, _sShip->getPower(), _blocksVec))
			//		{
			//			_sShip->setCarrier(nullptr);
			//		}
			//	}
			//}

			if (_sShip->arrivedExit())
			{
				_shipDir = 0;
				_smallArrived = true;
				_sShip->del();
			}

		}
		else if (!_bShip->arrivedExit()) {
			if (!_smallArrived)// preventing big ship to delete small ship
				_sShip->putOnBoard();

			didMove = _bShip->move(xDiff, yDiff, _bShip->getPower(), _blocksVec);
			//carrier = _bShip->getCarrier();
			//if (carrier != nullptr && didMove)
			//{
			//	//				if (yDiff >= 0)
			//	//				{
			//	if (!carrier->move(xDiff, yDiff, _bShip->getPower(), _blocksVec))
			//	{
			//		if (yDiff == 0)
			//			_bShip->setCarrier(nullptr);
			//	}
			//	//				}
			//}

			if (_bShip->arrivedExit())
			{
				_shipDir = 0;
				_bigArrived = true;
				_bShip->del();
			}
		}
	}
}
/*
* this function handle the "pause game" in case the user chose to pause the game.
*/
bool Game::pauseGame()const
{
	bool toContinue = true;
	clrscr();
	printPauseScreen();

	while (toContinue)
	{
		int key = 0;
		if (_kbhit())
		{
			key = _getch();
			if (key == Keys::ESC)
				break;
			if (key == Keys::ExitKey)
			{
				toContinue = false;
			}
		}

	}
	clrscr();
	return toContinue;
}
bool Game::gravitateAllBlocks() {

	char v;
	Block* p;

	for (int i = 0; i < _blocksVec.size(); i++)
	{
		p = _blocksVec[i];
		v = p->gravity();

		if (v == Signs::SmallSign)
		{
			if (p != _sShip->getCarrier())
			{
				if (p->getSize() > _sShip->getPower())
				{
					death();
					printLives();
					return false;
				}
				else {
					_sShip->setCarrierAtIndex(i,p);
					p->setShipToMoveWith(_sShip);
					p->setHasMoved(false);
				}
			}
		}
		if (v == Signs::BigSign)
		{
			if (p->getSize() > _bShip->getPower())
			{
				death();
				printLives();
				return false;
			}
			else {
				_bShip->setCarrierAtIndex(i, p);
				p->setShipToMoveWith(_bShip);
				p->setHasMoved(false);
			}
		}
		if (v == Signs::Space)
		{
			if (p->getShipToMoveWith() != nullptr)
			{
				p->getShipToMoveWith()->setCarrierAtIndex(i,nullptr);
				p->setShipToMoveWith(nullptr);
			}
		}

	}
	
	return true; // all blocks did not kill any ship - can return true!

}
bool Game::moveAllGhosts() {
	for (auto g : _ghostsVec)
	{
		if (!g->move())
			if (g->getHitShip())
			{
				death();
				printLives();
				return false;

			}

	}
	return true; //no ghost hit any ship - all can move forward!

}

/*
* void function that prints the user instractions.
*/
void Game::printInstructions() const
{
	clrscr();
	static char instructionsScreen[Sizes::BoardHeight][Sizes::BoardWidth] = {
	"******************************************************************************\n",
	"*                                                                            *\n",
	"*                    ThunderBirds - Instructions:                            *\n",
	"*   You must reach the exit position with both big and small spaceships,     *\n",
	"*   before countdown is over. If time is up, one life will go down.          *\n",
	"*   Big spaceship can push blocks with the maximum total size of 6,          *\n",
	"*   Small spaceship can push blocks with the maximum total size of 2.        *\n",
	"*   Each block that is located 'in the air' will fall down,                  *\n",
	"*   But if it falls on top of a spachship that is 'weaker' than that block,  *\n",
	"*   another life will go down. If you lose 3 lives - game is over.           *\n",
	"*                           ~ GOOD LUCK! ~                                   *\n",
	"*                                                                            *\n",
	"*  Symbols:    '@'   - Big spaceship                                         *\n",
	"*              '$'   - Small spaceship                                       *\n",
	"*              'W'   - Walls                                                 *\n",
	"*              'E'   - Exit position                                         *\n",
	"*            '0'-'9' - Blocks                                                *\n",
	"*  Keys:                                                                     *\n",
	"*          'B' - Move with big spaceship                                     *\n",
	"*          'S' - Move with small spaceship                                   *\n",
	"*          'W' - Up        ,       'X' - Down                                *\n",
	"*          'A' - Left      ,       'D' - Right                               *\n",
	"*          ESC - Pause game                                                  *\n",
	"*                                              Press any key to continue...  *\n",
	"******************************************************************************\0" };


	for (int r = 0; r < Sizes::BoardHeight; r++)
	{
		for (int c = 0; c < Sizes::BoardWidth; c++)
			cout << instructionsScreen[r][c];

	}

	pressAnyKeyToContinue();
}


void Game::printPauseScreen() const
{
	static char pauseScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] =
	{
		"*******************************************************************************\n",
		"*                                                                             *\n",
		"*                             .B@@&^   ^&@@B.                                 *\n",
		"*                             7@@@@P   P@@@@7                                 *\n",
		"*                             7@@@@P   P@@@@7                                 *\n",
		"*                             7@@@@P   P@@@@7                                 *\n",
		"*                             7@@@@P   P@@@@7                                 *\n",
		"*                             7@@@@P   P@@@@7                                 *\n",
		"*                             .B@@&:   ^&@@B.                                 *\n",
		"*                                                                             *\n",
		"*                                                                             *\n",
		"*                             - GAME PAUSED! -                                *\n",
		"*                    Press ESC to continue, or 9 to exit game...              *\n",
		"*                                                                             *\n",
		"*******************************************************************************\0"
	};

	cout << "\n\n\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << pauseScreen[r][c];

	}
	pressAnyKeyToContinue();


}
/*
* this is avoid function that prints to the screen a massage in case the player won.
*/
void  Game::printWinningScreen() const {
	clrscr();



	static char winningScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] =
	{		
			"*******************************************************************************\n",
			"*    ____                            _         _       _   _                  *\n",
			"*   / ___|___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_(_) ___  _ __  ___  *\n",
			"*  | |   / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __| *\n",
			"*  | |__| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\__ \\ *\n",
			"*   \\____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___/ *\n",
			"*                    |___/                                                    *\n",
			"*                                                                             *\n",
			"*                                                                             *\n",
			"*                                                                             *\n",
			"*          You have won this level!! Press ANY key to continue...             *\n",
			"*                                                                             *\n",
			"*                                                                             *\n",
			"*                                                                             *\n",
			"*******************************************************************************\0"
	};



	cout << "\n\n\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << winningScreen[r][c];

	}
	pressAnyKeyToContinue();

}
/*
* this is a void function that prints to the screen a massage in case the player won.
*/

void  Game::printLossScreen() const {
	clrscr();
	static char lossScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] =
	{
			"*******************************************************************************\n",
			"*                               _____________                                 *\n",
			"*                             ^/             \\^                               *\n",
			"*                             ^|             |^                               *\n",
			"*                             ^|             |^                               *\n",
			"*                             ^|  R . I . P  |^                               *\n",
			"*                             ^|             |^                               *\n",
			"*                             ^|             |^                               *\n",
			"*                            .P|:::::::::::::|P.                              *\n",
			"*                          ^YYYYYYYYYYYYYYYYYYYYY^                            *\n",
			"*                         ~~P77777777777777777777P~~                          *\n",
			"*                                                                             *\n",
			"*    SORRY, You have lost all your lives. that means you have lost the game!  *\n",
			"*                        Press any key to continue...                         *\n",
			"*******************************************************************************\0"	
	};



	cout << "\n\n\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << lossScreen[r][c];

	}
	pressAnyKeyToContinue();
	pressAnyKeyToContinue();
}

/*
* Function that clear the buffer from the last char.
*/
void Game::pressAnyKeyToContinue()const
{
	char key = 0;
	while (!key)
	{
		if (_kbhit())
		{
			key = _getch(); //clear buffer from last char
			break;
		}
	}
}


/*
* destractor
*/
Game::~Game()
{

	delete _bShip;
	delete _sShip;
	for (int i = 0; i < _blocksVec.size(); i++)
	{
		delete _blocksVec[i];
	}
	// next function does not work only with debugger:
	//freeBlocksVec(_blocksVec);

}


