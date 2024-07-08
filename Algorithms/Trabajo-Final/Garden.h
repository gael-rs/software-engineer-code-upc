#pragma once
#include "PlatingPlace.h"

class Garden
{
private:
	vector<PlatingPlace*>* platingPlaces;

public:
	Garden();
	~Garden();
	PlatingPlace* getPlatingPlace(short pos);
	void addPlatingPlace(PlatingPlace* platingPlace);
	void paintAllGarden(Graphics^ g);
	vector<short>* getIdxsAvailables();
	vector<short>* getIdxsPlanted();
	void sow(short idx, Vegetable* vegetable);
	short getN();
	PlatingPlace* collisionPoint(Point point);
};

