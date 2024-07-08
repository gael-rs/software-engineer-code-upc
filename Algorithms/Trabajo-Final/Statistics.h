#pragma once
#include "fstream"
#include "Macros.h"

struct LevelInfo {
	short moneyFarmer;
	const char* name;
};

class Statistics
{
private:
	string filePath;
	// Structura
	LevelInfo levelInfo;
	// Lectura
	ifstream* fileIfStream;
	// Escritura
	ofstream* fileOfStream;

public:
	Statistics();
	~Statistics();
	LevelInfo getLevelInfo();
	void save(LevelInfo li);
	void openFile();
};


