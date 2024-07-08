#pragma once
#include "Animal.h"

class Racoon : public Animal
{
private:


public:
	Racoon(short x = 0, short y = 0);
	~Racoon();
	void paint(Graphics^ g);
	void eat();
};
