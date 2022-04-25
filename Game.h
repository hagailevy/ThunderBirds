#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "Ghost.h"
#include "utils.h"

struct GameConstants {
	constexpr static int DebugSleep = 150;
	constexpr static int NormalSleep = 80;
	constexpr static int SecondSleep = 1000;
	constexpr static int CountdownPerLife = 1000;
};
/**/
class Game
{
	Board board;
	Ship* _sShip;
	Ship* _bShip;
	char _fileNum = 'a';

	std::vector<Block*> _blocksVec;
	int _numBlocks;
	std::vector<Ghost*> _ghostsVec;
	int _numGhosts;

	int _activeShip = Keys::Big;
	int _shipDir = 0;
	bool _bigArrived = false, _smallArrived = false;
	int _sleepInterval;
	int _lives = 3;
	bool _exit = false;

	vector<bool> _blocksCarriedByBigShip;
	vector<bool> _blocksCarriedBySmallShip;

private:
	void readFromFilesOrdered();
	void loadScreen(const ifstream& file);
	void printBadFile(const string& fileName);

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
	
	void printBlocksVec(); // functions for blocks vector usings:
	void delBlocksVec();
	void setBlocksVec();
	std::vector<Block*> duplicateBlocksVec(std::vector<Block*> origVec);
	void freeBlocksVec(std::vector<Block*> vec);


	void printGhostsVec(); // functions for ghosts vector usings :
	void delGhostVec();
	void setGhostsVec();
	vector<Ghost*> duplicateGhostsVec(vector<Ghost*> origVec);
	void freeGhostsVec(std::vector<Ghost*> vec);
	
	bool gravitateAllBlocks();
	bool moveAllGhosts();
	
	void death();
	void tickDown(int timeCounter, int& countDown);
public:
	Game(int sleepInterval = GameConstants::NormalSleep);
	Game(const Game& other);

	void runKeys();
	void run();
	~Game();

};
