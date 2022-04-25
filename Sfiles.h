#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
using namespace std;
class sFiles {

	int timer = 0;
	ifstream _screenFiles;
	string _screenFileName;
public:
	void closeFile();
	int getTimer() const;
	void setTimer();
	
	void openFileScreenWrite();
	void setNameFileScreen(const string& fileName);
	void openFiles(const string& fileName);
	void openFileToRead();
	void openFileToWrite();
	int intReadFileSteps();
	void openFileScreenRead();
	char readFileScreens();
	bool endOfFileBool();
	vector<string> getFilesNames();

};

