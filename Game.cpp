#include <conio.h>
#include <cctype>
#include <windows.h>
#include <iostream>
#include<fcntl.h>
#include <io.h>
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
	_sShip = new Ship(smallShipPoints, 2, Signs::SmallSign,Sizes::SmallPower);
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

	vector<Point> block6Points({ { 11,7 },{ 11,6 },{ 11,5 } });
	Block* block6 = new Block(block6Points, 3, '6');

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
	cout << "\n\t\t   Welcome to ThunderBirds!" << endl << endl;
	cout << "\t\ta) Click 1 to start a new game." << endl;
	cout << "\t\tb) Click 8 for instructions and keys." << endl;
	cout << "\t\tc) Click 9 to exit." << endl;

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

		while (_lives > 0 && (!_bigArrived || !_smallArrived) && !_exit)
		{
			_sShip->draw();
			_bShip->draw();
			printBlocksVec();
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


		}

		delete pBigShipSaver;
		delete pSmallShipSaver;
		freeBlocksVec(blockSaverVec);

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


		char v;
		for (Block* p : _blocksVec)
		{
			v = p->gravity();
			if (v == Signs::SmallSign && p->getHasMoved())
			{
				if (p != _sShip->getCarrier())
				{
					if (p->getSize() > _sShip->getPower())
					{
						death();
						printLives();
						return;
					}
					else {
						_sShip->setCarrier(p);
						p->setHasMoved(false);
					}
				}
			}
			if (v == Signs::BigSign && p->getHasMoved())
			{
				if (p->getSize() > _bShip->getPower())
				{
					death();
					printLives();
					return;
				}
				else {
					_bShip->setCarrier(p);
					p->setHasMoved(false);
				}
			}
		}

		startMoving();

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
	_sShip->del();
	delBlocksVec();
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
			carrier = _sShip->getCarrier();
			if (carrier != nullptr && didMove) //case block fell on ship - then ship needs to carry it
			{
				if (yDiff >= 0) //only for right and left (otherwise block already moved)
				{
					if (!carrier->move(xDiff, yDiff, _sShip->getPower(), _blocksVec))
					{
							_sShip->setCarrier(nullptr);
					}
				}
			}

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
			carrier = _bShip->getCarrier();
			if (carrier != nullptr && didMove)
			{
//				if (yDiff >= 0)
//				{
					if (!carrier->move(xDiff, yDiff, _bShip->getPower(), _blocksVec))
					{
						if(yDiff==0)
							_bShip->setCarrier(nullptr);
					}
//				}
			}
			{}
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

/*
* void function that prints the user instractions.
*/
void Game::printInstructions() const
{
	clrscr();
	static char instructionsScreen[Sizes::InGameScreens_HEIGHT+19][Sizes::InGameScreens_WIDTH+28] = {
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


	for (int r = 0; r < Sizes::InGameScreens_HEIGHT + 19; r++)
	{
		for (int c = 0; c < Sizes::InGameScreens_WIDTH + 28; c++)
			cout << instructionsScreen[r][c];

	}

	pressAnyKeyToContinue();
}


void Game::printPauseScreen() const
{
	static char pauseScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] = {
		"**************************************************\n",
		"*                                                *\n",
		"*                 GAME PAUSED!                   *\n",
		"*     Press ESC to continue, or 9 to exit game   *\n",
		"*                                                *\n",
		"**************************************************\0" };
	
	cout << "\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		cout << "\t     ";
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << pauseScreen[r][c];

	}
	


}
/*
* this is avoid function that prints to the screen a massage in case the player won.
*/
void  Game::printWinningScreen() const {
	clrscr();
	static char winningScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] = {
		"**************************************************\n",
		"*                                                *\n",
		"*                CONGRATS, You have won!         *\n",
		"*            Press any key to continue...        *\n",
		"*                                                *\n",
		"**************************************************\n" };

	cout << "\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		cout << "\t     ";
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << winningScreen[r][c];

	}
	pressAnyKeyToContinue();

}
/*
* this is a void function that prints to the screen a massage in case the player won.
*/

void  Game::printLossScreen() const{
	clrscr();
	static char lossScreen[Sizes::InGameScreens_HEIGHT][Sizes::InGameScreens_WIDTH] = {
		"**************************************************\n",
		"*                                                *\n",
		"*          SORRY, You have lost all your         *\n",
		"*     lives, that means you have lost the game!  *\n",
		"*           Press any key to continue...         *\n",
		"**************************************************\n" };

	cout << "\n\n\n";
	for (int r = 0; r < Sizes::InGameScreens_HEIGHT; r++)
	{
		cout << "\t     ";
		for (int c = 0; c < Sizes::InGameScreens_WIDTH; c++)
			cout << lossScreen[r][c];

	}

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



