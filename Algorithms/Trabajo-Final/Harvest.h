#pragma once
#include "Item.h"
#include "Vegetable.h"

class Harvest: public Item
{
private:
	Vegetable* vegetable;

public:
	Harvest(Vegetable* vegetable);
	~Harvest();	
	void paint(Graphics^ g);
	BaseEntity* getEntity();
	short getSalePrice();
};

