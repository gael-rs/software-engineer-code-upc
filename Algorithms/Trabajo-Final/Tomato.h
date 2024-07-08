#pragma once
#include "Vegetable.h"

class Tomato : public Vegetable
{
private:


public:
	Tomato();
	~Tomato();
	void paintSeed(Graphics^ g);
	void paintPlant(Graphics^ g);
	void paintHarvest(Graphics^ g);
	Tomato* clone();
};
