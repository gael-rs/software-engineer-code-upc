#include "Statistics.h"

Statistics::Statistics()
{
	fileIfStream = new ifstream;
	fileOfStream = new ofstream;
	levelInfo = LevelInfo();
	filePath = FILE_SAVED_PATH;
}

Statistics::~Statistics()
{
	delete fileIfStream;
	delete fileOfStream;
}

LevelInfo Statistics::getLevelInfo()
{
	return levelInfo;
}


void Statistics::save(LevelInfo li)
{
	fileOfStream->write((const char*)&li, sizeof(LevelInfo));
	fileOfStream->close();
}

void Statistics::openFile()
{
	fileOfStream->open(filePath.c_str(), ios::out | ios::binary);

	if (fileOfStream->is_open()) {
		fileIfStream->open(filePath.c_str(), ios::in | ios::binary);
	}
}
