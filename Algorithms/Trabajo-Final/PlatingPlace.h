#pragma once
#include "Plant.h"
#include "Harvest.h"
#include "Pot.h"

class PlatingPlace
{
private:
	Plant* plant;
	Pot* pot;

public:
	PlatingPlace(short x = 0, short y = 0);
	~PlatingPlace();

	void paintEverything(Graphics^ g);
	void sow(Vegetable* vegetable);
	Pot* getPot();
	Plant* getPlant();
	bool collision(BaseEntity* entity);
	bool collision(Point point);
	Harvest* getHarvest();
	void removePlant();
};

