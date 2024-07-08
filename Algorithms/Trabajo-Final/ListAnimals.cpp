#include "ListAnimals.h"

ListAnimals::ListAnimals()
{
	animals = new vector<Animal*>;
	timeOfRefill = 20;
}

ListAnimals::~ListAnimals()
{
	delete animals;
}

void ListAnimals::addAnimal(Animal* animal)
{
	this->animals->push_back(animal);
}

void ListAnimals::removeAnimal(short pos)
{
	this->animals->erase(animals->begin() + pos);
}

Animal* ListAnimals::getAnimal(short pos)
{
	return animals->at(pos);
}

void ListAnimals::moveAnimals(Graphics^ g, Rectangle* space)
{
	for (short i = 0; i < animals->size(); i++) {
		Animal* animal = animals->at(i);

		if (
			(animal->getTurned() && animal->getObjetive() >= 0
				&& animal->getSecondsSinceLighting() == 3 && animal->getLighted())
			|| (animal->getTurned() && animal->getObjetive() >= 0
				&& animal->getSecondsSinceCrashed() == 2 && animal->getCrashed())
			|| (animal->getObjetive() >= 0 && animal->getTurned()
				&& !animal->getEated() && !animal->getCrashed() && !animal->getLighted())
			) {
			if (animal->getLighted() && animal->getSecondsSinceLighting() == 3) {
				animal->setLighted(false);
			}

			if (animal->getSecondsSinceLighting() == 3 && animal->getEated()) {
				animal->move(g);
				if (!space->IntersectsWith(*animal->getRectangle())) animals->erase(animals->begin() + i);
				return;
			};

			animal->setDx(-1 * animal->getDx());
			animal->setTurned(false);
		};

		Dog* dog = dynamic_cast<Dog*>(animal);
		if (dog != nullptr) dog->move(space);
		else animal->move(g);

		if (!space->IntersectsWith(*animal->getRectangle())) animals->erase(animals->begin() + i);
	}
}

void ListAnimals::paintAnimals(Graphics^ g)
{
	for (short i = 0; i < animals->size(); i++) {
		animals->at(i)->paint(g);
	}
}

void ListAnimals::checkObjective(vector<short>* idxsPlanted)
{
	for (short i = 0; i < animals->size(); i++) {
		if (!animals->at(i)->getEated()) {
			vector<short>* idxsPlantedPosibleObjective = new vector<short>;
			for (short j = 0; j < idxsPlanted->size(); j++) {
				if (animals->at(i)->getColumnGarden() == trunc(float(idxsPlanted->at(j)) / 4.0) &&
					!existsAnimalWithObjective(idxsPlanted->at(j))) {
					idxsPlantedPosibleObjective->push_back(idxsPlanted->at(j));
				}
			}

			if (idxsPlantedPosibleObjective->size() > 0) {
				animals->at(i)->setObjective(
					idxsPlantedPosibleObjective->at(rand() % idxsPlantedPosibleObjective->size())
				);
			}
			delete idxsPlantedPosibleObjective;
		}

	}
}

Animal* ListAnimals::collisionAnimal(BaseEntity* entity)
{
	for (short i = 0; i < animals->size(); i++)
	{
		if (animals->at(i)->getName() != "Perro" && animals->at(i)->collision(entity)) return animals->at(i);
	}
	return nullptr;
}

short ListAnimals::getN()
{
	return animals->size();
}

short ListAnimals::getTimeOfRefill()
{
	return timeOfRefill;
}

void ListAnimals::fill(Rectangle* space)
{
	Animal* animal = nullptr;
	Point* point = new Point(space->Width - space->Width * 2 / 40);

	for (short i = 0; i < 4; i++) {
		short randValue = rand() % 5;

		point->Y = space->Y + short(space->Height * 2 / 16)
			+ i * short(space->Height * 2 / 16) + i * short(space->Height * 1.5 / 16) - 8;

		if (randValue == 0) animal = new Mole(point->X, point->Y);
		else if (randValue == 1) animal = new Bat(point->X, point->Y);
		else if (randValue == 2) animal = new Racoon(point->X, point->Y);
		else if (randValue == 3) animal = new Rabbit(point->X, point->Y);

		if (animal != nullptr) {
			animal->setColumnGarden(i);
			addAnimal(animal);
		}

		animal = nullptr;
	}

	delete point;
	delete animal;
}

void ListAnimals::setStartOfRefill(clock_t startOfRefill)
{
	this->startOfRefill = startOfRefill;
}

short ListAnimals::getSecondsStartOfRefill()
{
	return (clock() - startOfRefill) / CLOCKS_PER_SEC;
}

bool ListAnimals::existsAnimalWithObjective(short idx)
{
	for (short i = 0; i < animals->size(); i++) {
		if (trunc(float(idx / 4.0)) == animals->at(i)->getColumnGarden() &&
			animals->at(i)->getObjetive() == idx) return true;
	}

	return false;
}

void ListAnimals::stopEverything()
{
	for (short i = 0; i < animals->size(); i++) {
		animals->at(i)->stop();
	}
}
void ListAnimals::playEverything()
{
	for (short i = 0; i < animals->size(); i++) {
		animals->at(i)->play();
	}
}

void ListAnimals::positionAnimal(Animal* animal, Rectangle* space, short index)
{
	short i = index >= 0 ? index : rand() % 4;

	Point* point = new Point(
		space->X + space->Width * 1 / 4 - 37
	);

	short randValue = rand() % 5;

	point->Y = space->Y + short(space->Height * 2 / 16)
		+ i * short(space->Height * 2 / 16) + i * short(space->Height * 1.5 / 16) - 8;

	animal->setX(point->X);
	animal->setY(point->Y);

	delete point;
}
