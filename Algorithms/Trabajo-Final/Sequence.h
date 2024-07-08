#pragma once
#include "AnimateEntity.h"

enum Position {
	CenterY,
	CenterX,
	CenterXY,
	NormalXY,
};

class Sequence : public AnimateEntity
{
private:
	short columns, rows;
	float scale;
	char* srcBitmap;
	bool play, loop, isFinished;
	Position position;

public:
	Sequence(short columns = 1, short rows = 1, string srcBitmap = "", float scale = 1.0, Position position = Position::NormalXY);
	~Sequence();

	void paint(Graphics^ g);
	short getColumns();
	void setColumns(short columns);
	short getRows();
	void setRows(short columns);
	bool getPlay();
	void setPlay(bool play);
	float getScale();
	void setScale(float scale);
	bool getLoop();
	void setLoop(bool loop);
	void setSrcBitMap(string srcBitMap);
	bool getIsFinished();
};

