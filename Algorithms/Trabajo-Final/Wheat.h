#pragma once
#include "Vegetable.h"

class Wheat : public Vegetable
{
private:


public:
	Wheat();
	~Wheat();
	void paintSeed(Graphics^ g);
	void paintPlant(Graphics^ g);
	void paintHarvest(Graphics^ g);
	Rectangle* getMeasuresHarvest();
	Wheat* clone();
};
