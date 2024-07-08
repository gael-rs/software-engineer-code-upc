#pragma once
#include "StaticEntity.h"

class Vegetable : public StaticEntity
{
protected:
	short price, growthInterval, timeToBeEaten, salePrice;

public:
	Vegetable();
	~Vegetable();
	virtual void paintSeed(Graphics^ g) {};
	virtual void paintPlant(Graphics^ g) {};
	virtual void paintHarvest(Graphics^ g) {};
	virtual Rectangle* getMeasuresHarvest() { return nullptr; };
	virtual Vegetable* clone();
	short getPrice();
	short getTimeToBeEaten();
	short getSalePrice();
	short getGrowthInterval();
};


