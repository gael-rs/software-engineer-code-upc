#include "Plant.h"

Plant::Plant(Vegetable* vegetable)
{
	startSowed = clock();
	startedBeEaten = false;
	this->vegetable = vegetable;
}

Plant::~Plant()
{
	delete vegetable;
}

void Plant::paint(Graphics^ g)
{
	vegetable->paintPlant(g);

	checkTime();
}

void Plant::checkTime()
{
	short* seconds = new short;
	*seconds = (clock() - startSowed) / CLOCKS_PER_SEC;

	if (*seconds <= vegetable->getGrowthInterval()) {
		vegetable->setColumn(short(round(float((*seconds)) / float(vegetable->getGrowthInterval() * 0.5))));
	}

	delete seconds;
}

Vegetable* Plant::getVegetable()
{
	return vegetable;
}

bool Plant::getStartedBeEaten()
{
	return startedBeEaten;
}

void Plant::setStartedBeEaten(bool startedBeEaten)
{
	this->startedBeEaten = startedBeEaten;
}

void Plant::setStartBeEaten(clock_t startBeEaten)
{
	this->startBeEaten = startBeEaten;
}

bool Plant::checkFinishEaten()
{
	if (startedBeEaten) {
		short* seconds = new short;
		*seconds = (clock() - startBeEaten) / CLOCKS_PER_SEC;

		if (startedBeEaten && *seconds > vegetable->getTimeToBeEaten()) {
			startedBeEaten = false;
			delete seconds;
			return true;
		}
		delete seconds;
	}

	return false;
}

bool Plant::collision(BaseEntity* entity)
{
	bool collision = false;
	Rectangle* moldVegetable = new Rectangle((vegetable->getX() + vegetable->getWidth() * 1 / 3), 
		vegetable->getY(), vegetable->getWidth() * 1 / 3, vegetable->getHeight());

	collision = moldVegetable->IntersectsWith(*entity->getRectangle());

	delete moldVegetable;

	return collision;
}

bool Plant::collision(Point point)
{
	return  vegetable->getRectangle()->Contains(point);
}
