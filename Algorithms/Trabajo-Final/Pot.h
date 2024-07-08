#pragma once
#include "StaticEntity.h"

class Pot : public StaticEntity
{
private:
	bool planted;

public:
	Pot(short x = 0, short y = 0);
	~Pot();
	void paint(Graphics^ g);
	void setPlanted(bool planted);
	bool getPlanted();
	Rectangle* getRectangle();
};

