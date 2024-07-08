#include "Animal.h"

Animal::Animal(short x, short y) : AnimateEntity(x, y)
{
	eating = eated = crashed = lighted = stoped = chasedAway = false;
	dx = -4;
	objective = -1;
	timeLighting = clock();
}

Animal::~Animal()
{
}

void Animal::move(Graphics^ g)
{
	if (objective < 0 && dx > 0 && x + width + dx >= g->VisibleClipBounds.Width) {
		turned = !turned;
		dx *= -1;
	}

	x += dx;
}

bool Animal::getEating()
{
	return eating;
}

void Animal::stop()
{
	stoped = true;
}

void Animal::play()
{
	stoped = false;
}

void Animal::setEating(bool eating)
{
	this->eating = eating;
}

bool Animal::getCrashed()
{
	return crashed;
}

void Animal::setCrashed(bool crashed)
{
	this->crashed = crashed;
}

bool Animal::getLighted()
{
	return lighted;
}

void Animal::setLighted(bool lighted)
{
	this->lighted = lighted;
}

short Animal::getObjetive()
{
	return objective;
}

clock_t Animal::getTimeLighting()
{
	return timeLighting;
}

short Animal::getSecondsSinceLighting()
{
	return (clock() - timeLighting) / CLOCKS_PER_SEC;
}

short Animal::getSecondsSinceCrashed()
{
	return (clock() - timeCrashed) / CLOCKS_PER_SEC;
}

short Animal::getColumnGarden()
{
	return columnGarden;
}

bool Animal::getChasedAway()
{
	return chasedAway;
}

void Animal::setChasedAway(bool chasedAway)
{
	this->chasedAway = chasedAway;
}

void Animal::setTimeLighting(clock_t timeLighting)
{
	this->timeLighting = timeLighting;
}

void Animal::setTimeCrashed(clock_t timeCrashed)
{
	this->timeCrashed = timeCrashed;
}

void Animal::setObjective(short objective)
{
	this->objective = objective;
}

void Animal::setColumnGarden(short columnGarden)
{
	this->columnGarden = columnGarden;
}

short Animal::getEated()
{
	return eated;
}

void Animal::setEated(bool eated)
{
	this->eated = eated;
}

bool Animal::actionForCollisionWall()
{
	timeCrashed = clock();
	crashed = true;
	dx *= -1;
	turned = true;
	return true;
}

void Animal::eat()
{
	if (!stoped) {
		eating = true;
		dx = 0;
	}
}
