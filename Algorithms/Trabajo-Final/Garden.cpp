#include "Garden.h"

Garden::Garden()
{
    platingPlaces = new vector<PlatingPlace*>;
}

Garden::~Garden()
{
    delete[] platingPlaces;
}

PlatingPlace* Garden::getPlatingPlace(short pos)
{
    if (pos < 0) return nullptr;
    return platingPlaces->at(pos);
}

void Garden::addPlatingPlace(PlatingPlace* platingPlace)
{
    platingPlaces->push_back(platingPlace);
}

void Garden::paintAllGarden(Graphics^ g)
{
    for (short i = 0; i < platingPlaces->size(); i++) platingPlaces->at(i)->paintEverything(g);
}

vector<short>* Garden::getIdxsAvailables()
{
    vector<short>* idxsAvailables = new vector<short>;

    for (short i = 0; i < platingPlaces->size(); i++) {
        if (!platingPlaces->at(i)->getPot()->getPlanted()) idxsAvailables->push_back(i);
    }

    return idxsAvailables;
}

vector<short>* Garden::getIdxsPlanted()
{
    vector<short>* idxsPlanted = new vector<short>;

    for (short i = 0; i < platingPlaces->size(); i++) {
        if (platingPlaces->at(i)->getPot()->getPlanted()) idxsPlanted->push_back(i);
    }

    return idxsPlanted;
}

void Garden::sow(short idx, Vegetable* vegetable)
{
    platingPlaces->at(idx)->getPot()->setPlanted(true);
    platingPlaces->at(idx)->sow(vegetable);
}

short Garden::getN()
{
    return platingPlaces->size();
}

PlatingPlace* Garden::collisionPoint(Point point)
{
    for (short i = 0; i < platingPlaces->size(); i++) {
        if (platingPlaces->at(i)->collision(point)) return platingPlaces->at(i);
    }
    return nullptr;
}
