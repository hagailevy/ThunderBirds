#include "sFiles.h"
namespace fs = std::filesystem;
using namespace std;

int sFiles::getTimer() const {
	return timer;
}

void  sFiles::setTimer() {
	timer = timer + 1;
}

void sFiles::openFiles(const string& fileName) {
	setNameFileScreen(fileName);
}

void sFiles::openFileToWrite() {
	openFileScreenWrite();
	
}
void sFiles::openFileToRead() {
	openFileScreenRead();

}

void sFiles::setNameFileScreen(const string& fileName) {
	this->_screenFileName = fileName;
	this->_screenFileName.append(".screen");
}



void sFiles::openFileScreenWrite() {
	_screenFiles.open(_screenFileName, ios::out);
}



void sFiles::openFileScreenRead() {
	_screenFiles.open(_screenFileName, ios::in);
}


int sFiles::intReadFileSteps() {
	int x;
	_screenFiles >> x;
	_screenFiles.get();
	return x;
}

char sFiles::readFileScreens() {
	char ch;
	_screenFiles.get(ch);
	return ch;

}


bool sFiles::endOfFileBool() {
	return _screenFiles.eof();
}

void sFiles::closeFile() {
	_screenFiles.close();
}


vector<string> sFiles::getFilesNames()
{
	vector<string> filenames;
	fs::path a = fs::current_path();
	string firstname;
	//std::string path = fs;
	for (const auto& entry : fs::directory_iterator(a))
	{
		firstname = entry.path().filename().string();
		if (entry.path().extension().string() == ".screen" && firstname[0] == 't' && firstname[1] == 'b')
			filenames.push_back(entry.path().filename().string());
	}
	sort(filenames.begin(), filenames.end());
	return filenames;

}