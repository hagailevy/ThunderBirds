#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "utils.h"

struct GameConstants {
	constexpr static int DebugSleep = 150;
	constexpr static int NormalSleep = 80;
	constexpr static int SecondSleep = 1000;
	constexpr static int CountdownPerLife = 80;
};
/**/
class Game
{
	Board board;
	Ship* _sShip;
	Ship* _bShip;
	std::vector<Block*> _blocksVec;
	int _numBlocks;
	int _activeShip = Keys::Big;
	int _shipDir = 0;
	bool _bigArrived = false, _smallArrived = false;
	int _sleepInterval;
	int _lives = 3;
	bool _exit = false;
private:
	void pressAnyKeyToContinue() const;
	void chooseOptions();
	void printMenu()const;
	void printLives()const;
	void printInstructions() const;
	bool pauseGame() const ;
	void printPauseScreen()const;
	void printWinningScreen()const;
	void  printLossScreen()const;
	void startMoving();
	void hitKeys(char key);
	std::vector<Block*> duplicateBlocksVec(std::vector<Block*> origVec);
	void freeBlocksVec(std::vector<Block*> vec);
	void printBlocksVec();
	void delBlocksVec();
	void setBlocksVec();
	void death();
	void tickDown(int timeCounter, int& countDown);
public:
	Game(int sleepInterval = GameConstants::NormalSleep);

	void runKeys();
	void run();
	~Game();

};
