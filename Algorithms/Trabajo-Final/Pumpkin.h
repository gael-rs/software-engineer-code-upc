#pragma once
#include "Vegetable.h"

class Pumpkin : public Vegetable
{
private:


public:
	Pumpkin();
	~Pumpkin();
	void paintSeed(Graphics^ g);
	void paintPlant(Graphics^ g);
	void paintHarvest(Graphics^ g);
	Pumpkin* clone();
};
