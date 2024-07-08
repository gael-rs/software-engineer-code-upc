#include "PlatingPlace.h"


PlatingPlace::PlatingPlace(short x, short y)
{
	plant = nullptr;
	pot = new Pot(x, y);
}

PlatingPlace::~PlatingPlace()
{
	delete plant;
	delete pot;
}

void PlatingPlace::paintEverything(Graphics^ g)
{
	if (plant != nullptr) {
		plant->paint(g);
		bool plantEaten = plant->checkFinishEaten();
		if (plantEaten) {
			delete plant;
			plant = nullptr;
			pot->setPlanted(false);
		}
	}

	pot->paint(g);
}

void PlatingPlace::sow(Vegetable* vegetable)
{
	vegetable->setX(pot->getX());
	vegetable->setY(pot->getY() - vegetable->getHeight() + 12);

	plant = new Plant(vegetable);
}

Pot* PlatingPlace::getPot()
{
	return pot;
}

Plant* PlatingPlace::getPlant()
{
	return plant;
}

bool PlatingPlace::collision(BaseEntity* entity)
{
	if (pot->collision(entity)) return true;
	return plant->collision(entity);
}

bool PlatingPlace::collision(Point point)
{
	if (pot->getPlanted() && pot->getRectangle()->Contains(point)) return true;
	return plant != nullptr && plant->collision(point);
}

Harvest* PlatingPlace::getHarvest()
{
	return new Harvest(plant->getVegetable()->clone());
}

void PlatingPlace::removePlant()
{
	delete plant;
	plant = nullptr;
	pot->setPlanted(false);
}
