#pragma once
#include "Vegetable.h"

class Carrot : public Vegetable
{
private:


public:
	Carrot();
	~Carrot();
	void paintSeed(Graphics^ g);
	void paintPlant(Graphics^ g);
	void paintHarvest(Graphics^ g);
	Carrot* clone();
};