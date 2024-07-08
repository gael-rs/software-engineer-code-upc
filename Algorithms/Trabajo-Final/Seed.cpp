#include "Seed.h"

Seed::Seed(Vegetable* vegetable) : Item()
{
	this->vegetable = vegetable;
	type = "seed";
}

Seed::~Seed()
{
	delete vegetable;
}

void Seed::setVegetable(Vegetable* vegetable)
{
	this->vegetable = vegetable;
}

BaseEntity* Seed::getEntity()
{
	return getVegetable();
}

short Seed::getPrice()
{
	return vegetable->getPrice();
}

short Seed::getSalePrice()
{
	return vegetable->getSalePrice();
}

Vegetable* Seed::getVegetable()
{
	return vegetable;
}

void Seed::paint(Graphics^ g) 
{
	vegetable->paintSeed(g);
	Item::paint(g);
}