#pragma once
#include "Animal.h"
#include "Mole.h"
#include "Bat.h"
#include "Racoon.h"
#include "Rabbit.h"
#include "Carrot.h"
#include "Dog.h"

class ListAnimals
{
private:
	// Relación de agregación de la clase Animal con la clase ListAnimals
	vector<Animal*>* animals;
	short timeOfRefill;
	clock_t startOfRefill;

public:
	ListAnimals();
	~ListAnimals();
	void addAnimal(Animal* animal);
	void removeAnimal(short pos);
	Animal* getAnimal(short pos);
	void moveAnimals(Graphics^ g, Rectangle* space);
	void paintAnimals(Graphics^ g);
	void checkObjective(vector<short>* idxsPlanted);
	Animal* collisionAnimal(BaseEntity* entity);
	short getN();
	short getTimeOfRefill();
	void fill(Rectangle* space);
	void setStartOfRefill(clock_t startOfRefill);
	short getSecondsStartOfRefill();
	bool existsAnimalWithObjective(short idx);
	void stopEverything();
	void playEverything();
	void positionAnimal(Animal* animal, Rectangle* space, short index = -1);
};

