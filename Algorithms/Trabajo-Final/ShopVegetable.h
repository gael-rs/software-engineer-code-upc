#pragma once
#include "StaticEntity.h"
#include "Seed.h"
#include "Farmer.h"

class ShopVegetable : public StaticEntity
{
private:
	Seed* seed;

public:
	ShopVegetable(Vegetable* vegetable = nullptr);
	~ShopVegetable();
	Seed* getSeed();
	bool collisionPoint(Point point);
	void paint(Graphics^ g);
};
