#pragma once
#include "Animal.h"

class Bat : public Animal
{
private:


public:
	Bat(short x = 0, short y = 0);
	~Bat();
	void paint(Graphics^ g);
	bool actionForCollisionWall() { return false; };
	void eat();
};


