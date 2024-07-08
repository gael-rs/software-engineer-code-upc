#pragma once
#include "Vegetable.h"

class Plant
{
private:
	Vegetable* vegetable;
	clock_t startSowed;
	clock_t startBeEaten;
	bool startedBeEaten;

public:
	Plant(Vegetable* vegetable);
	~Plant();
	void paint(Graphics^ g);
	void checkTime();
	Vegetable* getVegetable();
	bool getStartedBeEaten();
	void setStartedBeEaten(bool startedBeEating);
	void setStartBeEaten(clock_t startBeEaten);
	bool checkFinishEaten();
	bool collision(BaseEntity* entity);
	bool collision(Point point);
};

