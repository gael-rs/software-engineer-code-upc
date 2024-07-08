#pragma once
#include "Animal.h"

class Mole : public Animal
{
private:
	bool makingHole, comingOutTheHole;

public:
	Mole(short x = 0, short y = 0);
	~Mole();
	void paint(Graphics^ g);
	bool getMakingHole();
	void setMakingHole(bool makingHole);
	void makeHole();
	bool actionForCollisionWall();
	Rectangle* getRectangle();
	void eat();
};
