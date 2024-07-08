#pragma once
#include "Item.h"
#include "Vegetable.h"

class Seed : public Item
{
private:
	Vegetable* vegetable;

public:
	Seed(Vegetable* vegetable = nullptr);
	~Seed();
	Vegetable* getVegetable();
	void paint(Graphics^ g);
	void setVegetable(Vegetable* vegetable);
	BaseEntity* getEntity();
	short getPrice();
	short getSalePrice();
};


