#pragma once
#include "Animal.h"

class Rabbit : public Animal
{
private:


public:
	Rabbit(short x = 0, short y = 0);
	~Rabbit();
	void paint(Graphics^ g);
	void eat();
};
