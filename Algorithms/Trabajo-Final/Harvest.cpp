#include "Harvest.h"

Harvest::Harvest(Vegetable* vegetable)
{
	this->vegetable = vegetable;
	type = "harvest";
}

Harvest::~Harvest()
{
}

void Harvest::paint(Graphics^ g)
{
	Rectangle* measures = vegetable->getMeasuresHarvest();
	if (measures != nullptr) vegetable->setWidth(-1);
	vegetable->paintHarvest(g);

	Item::paint(g);
}

BaseEntity* Harvest::getEntity()
{
	return vegetable;
}

short Harvest::getSalePrice()
{
	return vegetable->getSalePrice();
}